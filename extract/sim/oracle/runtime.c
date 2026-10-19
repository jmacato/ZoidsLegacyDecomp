/* Host versions of the GBA BIOS calls the oracle's decomp code makes (the decomp wraps them as svc instructions). */
int abi_080ECD30(int numerator, int denominator) {
    if (denominator == 0 || (numerator == (int)0x80000000 && denominator == -1)) return 0;
    return numerator / denominator;
}
