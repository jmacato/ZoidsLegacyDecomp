//! Build the browser page: template.html with style.css, decode.js, app.js and the gzip+base64 plan inlined.

use std::fs;
use std::io::Write;
use std::path::Path;

use flate2::write::GzEncoder;
use flate2::Compression;

fn base64(data: &[u8]) -> String {
    const TABLE: &[u8; 64] = b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    let mut out = String::with_capacity(data.len().div_ceil(3) * 4);
    for chunk in data.chunks(3) {
        let value = (u32::from(chunk[0]) << 16) | (u32::from(*chunk.get(1).unwrap_or(&0)) << 8) | u32::from(*chunk.get(2).unwrap_or(&0));
        for index in 0..4 {
            if index <= chunk.len() {
                out.push(TABLE[(value >> (18 - 6 * index) & 63) as usize] as char);
            } else {
                out.push('=');
            }
        }
    }
    out
}

pub fn build(plan: &Path, out: &Path) -> Result<String, String> {
    let dir = crate::repo_root().join("extract/page");
    let read = |name: &str| fs::read_to_string(dir.join(name)).map_err(|error| format!("{name}: {error}"));
    let plan_bytes = fs::read(plan).map_err(|error| format!("{}: {error}", plan.display()))?;
    let parsed: serde_json::Value = serde_json::from_slice(&plan_bytes).map_err(|error| format!("plan: {error}"))?;
    if parsed["rom_sha1"] != crate::EXPECTED_SHA1 {
        return Err("plan is not for Zoids Legacy (USA)".into());
    }
    let mut encoder = GzEncoder::new(Vec::new(), Compression::best());
    encoder.write_all(&plan_bytes).map_err(|error| error.to_string())?;
    let gzip = encoder.finish().map_err(|error| error.to_string())?;
    let html = read("template.html")?
        .replace("/*STYLE*/", &read("style.css")?)
        .replace("/*DECODE*/", &read("decode.js")?)
        .replace("/*M4A*/", &read("m4a.js")?)
        .replace("/*ENGINES*/", &[read("display.js")?, read("objects.js")?, read("zoid-animation.js")?, read("cas.js")?, read("../sim/web/battle-engine.js")?, read("../sim/web/battle-field.js")?].join("\n"))
        .replace("/*APP*/", &read("app.js")?)
        .replace("/*PLAN*/", &base64(&gzip));
    fs::write(out, &html).map_err(|error| format!("{}: {error}", out.display()))?;
    Ok(format!("wrote {} ({} bytes; plan {} bytes, {} gzipped)\n", out.display(), html.len(), plan_bytes.len(), gzip.len()))
}

#[cfg(test)]
mod tests {
    #[test]
    fn base64_padding() {
        assert_eq!(super::base64(b"Man"), "TWFu");
        assert_eq!(super::base64(b"Ma"), "TWE=");
        assert_eq!(super::base64(b"M"), "TQ==");
    }
}
