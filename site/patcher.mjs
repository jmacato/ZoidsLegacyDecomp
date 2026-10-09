// BPS specification by byuu (public domain):
// https://floating.muncher.se/byuu/bps/bps_spec.html
const table = Uint32Array.from({ length: 256 }, (_, value) => {
  for (let bit = 0; bit < 8; bit++) value = (value >>> 1) ^ ((value & 1) ? 0xedb88320 : 0);
  return value >>> 0;
});

export function crc32(bytes) {
  let crc = 0xffffffff;
  for (const byte of bytes) crc = (crc >>> 8) ^ table[(crc ^ byte) & 255];
  return (crc ^ 0xffffffff) >>> 0;
}

export function applyBps(source, patch) {
  if (patch.length < 19 || String.fromCharCode(...patch.subarray(0, 4)) !== 'BPS1') {
    throw new Error('error.patchInvalid');
  }
  const end = patch.length - 12;
  const footer = new DataView(patch.buffer, patch.byteOffset + end, 12);
  if (crc32(patch.subarray(0, patch.length - 4)) !== footer.getUint32(8, true)) {
    throw new Error('error.patchDamaged');
  }
  let position = 4;
  function number() {
    let value = 0;
    let shift = 1;
    while (position < end) {
      const byte = patch[position++];
      value += (byte & 127) * shift;
      if (!Number.isSafeInteger(value)) break;
      if (byte & 128) return value;
      shift *= 128;
      value += shift;
    }
    throw new Error('error.patchNumber');
  }
  const sourceSize = number();
  const targetSize = number();
  const metadataSize = number();
  if (sourceSize !== source.length || crc32(source) !== footer.getUint32(0, true)) {
    throw new Error('error.romMismatch');
  }
  if (targetSize < 1 || targetSize > 32 * 1024 * 1024 || metadataSize > end - position) {
    throw new Error('error.patchSizes');
  }
  position += metadataSize;
  const target = new Uint8Array(targetSize);
  let output = 0;
  let sourceOffset = 0;
  let targetOffset = 0;
  while (position < end && output < targetSize) {
    const instruction = number();
    const action = instruction % 4;
    const length = Math.floor(instruction / 4) + 1;
    if (length > targetSize - output) throw new Error('error.patchTargetSize');
    if (action === 0) {
      if (length > source.length - output) throw new Error('error.patchSourceSize');
      target.set(source.subarray(output, output + length), output);
      output += length;
    } else if (action === 1) {
      if (length > end - position) throw new Error('error.patchIncomplete');
      target.set(patch.subarray(position, position + length), output);
      position += length;
      output += length;
    } else {
      const delta = number();
      const offset = Math.floor(delta / 2) * (delta % 2 ? -1 : 1);
      if (action === 2) {
        sourceOffset += offset;
        if (sourceOffset < 0 || length > source.length - sourceOffset) {
          throw new Error('error.patchSourceOffset');
        }
        target.set(source.subarray(sourceOffset, sourceOffset + length), output);
        sourceOffset += length;
        output += length;
      } else {
        targetOffset += offset;
        if (targetOffset < 0 || targetOffset >= output) {
          throw new Error('error.patchOutputOffset');
        }
        // BPS permits overlapping copies to repeat bytes already written.
        for (let count = 0; count < length; count++) target[output++] = target[targetOffset++];
      }
    }
  }
  if (position !== end || output !== targetSize || crc32(target) !== footer.getUint32(4, true)) {
    throw new Error('error.patchChecksum');
  }
  return target;
}
