This is a reuploaded proect that utilizes RC4 stream cipher encryption to read a file (named input.txt) encrypts it using an pseudo random number generator, XORs it with
the plaintext of the input file, and outputs the result into another file (named output.txt).
This program utilizes KSA (Key Scheduling Algorithm), using a secret key to generate a permutation array. This permutation array is then used to generate a keystream used for encryption.
