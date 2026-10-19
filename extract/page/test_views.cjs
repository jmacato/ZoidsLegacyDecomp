// Run every view in plan.json through decode.js against the ROM and require each Rust check to hold.
// usage: node extract/page/test_views.cjs ROM PLAN
const fs = require("fs");
const crypto = require("crypto");
const decode = require("./decode.js");

async function main() {
  const [romPath, planPath] = process.argv.slice(2);
  const rom = new Uint8Array(fs.readFileSync(romPath));
  const plan = JSON.parse(fs.readFileSync(planPath, "utf8"));
  if (crypto.createHash("sha1").update(rom).digest("hex") !== plan.rom_sha1) throw new Error("ROM SHA-1 does not match the plan");
  const counts = {}, failures = [];
  for (const item of plan.items) {
    const [kind, address, , , , , views] = item;
    for (const view of views) {
      const key = view.t;
      counts[key] = (counts[key] || 0) + 1;
      try {
        const result = await decode.render(rom, address, view);
        if (result.check && !result.check.ok) failures.push(`${plan.kinds[kind]}@0x${address.toString(16)} ${view.t}: ${result.check.detail}`);
        if (result.image && (!result.image.width || !result.image.height)) failures.push(`${plan.kinds[kind]}@0x${address.toString(16)} ${view.t}: empty image`);
      } catch (error) {
        failures.push(`${plan.kinds[kind]}@0x${address.toString(16)} ${view.t}: ${error.message}`);
      }
    }
  }
  console.log("views:", JSON.stringify(counts));
  if (failures.length) {
    console.log(`${failures.length} failures`);
    for (const line of failures.slice(0, 30)) console.log("  " + line);
    process.exit(1);
  }
  console.log("all views decode and match their Rust checks");
}

main().catch(error => { console.error(error); process.exit(1); });
