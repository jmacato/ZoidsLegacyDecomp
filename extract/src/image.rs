//! Indexed PNG output and GBA tile/colour helpers.

/// BGR555 -> RGB888.
pub fn bgr555(color: u16) -> [u8; 3] {
    let expand = |value: u16| ((value & 0x1F) << 3 | (value & 0x1F) >> 2) as u8;
    [expand(color), expand(color >> 5), expand(color >> 10)]
}

/// An indexed PNG. `transparent`: palette index 0 is transparent.
pub fn indexed_png(width: u32, height: u32, pixels: &[u8], palette: &[[u8; 3]], transparent: bool) -> Vec<u8> {
    let mut out = Vec::new();
    {
        let mut encoder = png::Encoder::new(&mut out, width, height);
        encoder.set_color(png::ColorType::Indexed);
        encoder.set_depth(png::BitDepth::Eight);
        encoder.set_palette(palette.iter().flatten().copied().collect::<Vec<u8>>());
        if transparent {
            encoder.set_trns(vec![0u8]);
        }
        let mut writer = encoder.write_header().expect("png header");
        writer.write_image_data(pixels).expect("png data");
    }
    out
}

/// Lay out 8x8 tiles (one palette index per pixel, 64 per tile) in rows of `columns`.
pub fn tile_sheet(tiles: &[[u8; 64]], columns: usize) -> (u32, u32, Vec<u8>) {
    let columns = columns.max(1).min(tiles.len().max(1));
    let rows = tiles.len().div_ceil(columns).max(1);
    let (width, height) = (columns * 8, rows * 8);
    let mut pixels = vec![0u8; width * height];
    for (index, tile) in tiles.iter().enumerate() {
        let (x0, y0) = ((index % columns) * 8, (index / columns) * 8);
        for y in 0..8 {
            for x in 0..8 {
                pixels[(y0 + y) * width + x0 + x] = tile[y * 8 + x];
            }
        }
    }
    (width as u32, height as u32, pixels)
}

/// A 2bpp 8x8 tile (16 bytes, low bits = left pixel).
pub fn tile_2bpp(data: &[u8]) -> [u8; 64] {
    let mut tile = [0u8; 64];
    for (index, byte) in data.iter().take(16).enumerate() {
        for pixel in 0..4 {
            tile[index * 4 + pixel] = (byte >> (pixel * 2)) & 3;
        }
    }
    tile
}

/// A 4bpp 8x8 tile (32 bytes, low nibble = left pixel).
pub fn tile_4bpp(data: &[u8]) -> [u8; 64] {
    let mut tile = [0u8; 64];
    for (index, byte) in data.iter().take(32).enumerate() {
        tile[index * 2] = byte & 0xF;
        tile[index * 2 + 1] = byte >> 4;
    }
    tile
}

pub const GRAY4: [[u8; 3]; 4] = [[255, 255, 255], [170, 170, 170], [85, 85, 85], [0, 0, 0]];

/// An RGB PNG.
pub fn rgb_png(width: u32, height: u32, pixels: &[[u8; 3]]) -> Vec<u8> {
    let mut out = Vec::new();
    {
        let mut encoder = png::Encoder::new(&mut out, width, height);
        encoder.set_color(png::ColorType::Rgb);
        encoder.set_depth(png::BitDepth::Eight);
        let mut writer = encoder.write_header().expect("png header");
        writer.write_image_data(&pixels.iter().flatten().copied().collect::<Vec<u8>>()).expect("png data");
    }
    out
}

/// BGR555 colours as 8x8 swatches, 16 per row.
pub fn palette_swatch(data: &[u8]) -> Vec<u8> {
    let colors: Vec<[u8; 3]> = data.chunks_exact(2).map(|pair| bgr555(u16::from_le_bytes([pair[0], pair[1]]))).collect();
    let rows = colors.len().div_ceil(16).max(1);
    let (width, height) = (16 * 8, rows * 8);
    let mut pixels = vec![[0u8; 3]; width * height];
    for (index, color) in colors.iter().enumerate() {
        let (x0, y0) = ((index % 16) * 8, (index / 16) * 8);
        for y in 0..8 {
            for x in 0..8 {
                pixels[(y0 + y) * width + x0 + x] = *color;
            }
        }
    }
    rgb_png(width as u32, height as u32, &pixels)
}

/// 4bpp tiles as a grey sheet, 16 tiles per row (no palette is implied).
pub fn gray_tiles_4bpp(data: &[u8]) -> Vec<u8> {
    let tiles: Vec<[u8; 64]> = data.chunks(32).map(tile_4bpp).collect();
    let (width, height, pixels) = tile_sheet(&tiles, 16);
    let palette: Vec<[u8; 3]> = (0..16u8).map(|level| [level * 17, level * 17, level * 17]).collect();
    indexed_png(width, height, &pixels, &palette, false)
}

/// 4bpp tiles drawn with one 16-colour BGR555 palette.
pub fn tiles_4bpp(data: &[u8], palette: &[u8]) -> Vec<u8> {
    let tiles: Vec<[u8; 64]> = data.chunks(32).map(tile_4bpp).collect();
    let (width, height, pixels) = tile_sheet(&tiles, 16);
    let colors: Vec<[u8; 3]> = (0..16).map(|index| palette.get(index * 2..index * 2 + 2).map_or([0; 3], |pair| bgr555(u16::from_le_bytes([pair[0], pair[1]])))).collect();
    indexed_png(width, height, &pixels, &colors, true)
}

/// A BG tilemap (u16 entries: tile 0-9, h-flip 10, v-flip 11, palette bank 12-15) drawn from 4bpp tiles and BGR555 banks.
/// 8bpp is used when the tile data is exactly 64 bytes for each tile the map uses.
pub fn render_tilemap(tiles: &[u8], tilemap: &[u8], palette: &[u8], width_tiles: usize, eight: bool) -> Vec<u8> {
    let entries: Vec<u16> = tilemap.chunks_exact(2).map(|pair| u16::from_le_bytes([pair[0], pair[1]])).collect();
    let height_tiles = entries.len().div_ceil(width_tiles).max(1);
    let (width, height) = (width_tiles * 8, height_tiles * 8);
    let colors: Vec<[u8; 3]> = palette.chunks_exact(2).map(|pair| bgr555(u16::from_le_bytes([pair[0], pair[1]]))).collect();
    let mut pixels = vec![[0u8; 3]; width * height];
    for (index, entry) in entries.iter().enumerate() {
        let tile = (entry & 0x3FF) as usize;
        let bank = (entry >> 12) as usize;
        let size = if eight { 64 } else { 32 };
        let Some(data) = tiles.get(tile * size..tile * size + size) else { continue };
        let pixels_of = if eight { let mut tile = [0u8; 64]; tile.copy_from_slice(data); tile } else { tile_4bpp(data) };
        let bank = if eight { 0 } else { bank };
        let (x0, y0) = ((index % width_tiles) * 8, (index / width_tiles) * 8);
        for y in 0..8 {
            for x in 0..8 {
                let sx = if entry & 0x400 != 0 { 7 - x } else { x };
                let sy = if entry & 0x800 != 0 { 7 - y } else { y };
                let value = pixels_of[sy * 8 + sx] as usize;
                if value != 0 {
                    pixels[(y0 + y) * width + x0 + x] = colors.get(bank * 16 + value).copied().unwrap_or([255, 0, 255]);
                }
            }
        }
    }
    rgb_png(width as u32, height as u32, &pixels)
}
