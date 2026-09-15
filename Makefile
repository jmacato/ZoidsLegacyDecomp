.PHONY: verify

verify:
	@test -n "$(ROM)" || (echo "Set ROM to your Zoids Legacy (USA) ROM path."; exit 2)
	@python3 tools/verify.py --rom "$(ROM)"
