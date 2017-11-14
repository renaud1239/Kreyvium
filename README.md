Reference code of the KREYVIUM stream cipher
============================================

This is the reference code for the KREYVIUM stream cipher, a 128-bits variant of TRIVIUM published in A. Canteaut, S. Carpov, C. Fontaine, T. Lepoint, M. Naya-Plasencia, P. Paillier and R. Sirdey, "Stream ciphers: a practical solution for efficient homomorphic-ciphertext compression", Proceedings of the 23rd International Conference on Fast Software Encryption, Lecture Notes in Computer Science, vol. 9783, pp. 313-333, 2016.

This code is only a straight translation of the specification in the aforementioned paper, without any particular optimizations.

To compile the reference code, run it and compare its output to the reference just do:

    g++ kreyvium-ref.cpp
    ./a.out < kreyvium.dat > tmp
    diff tmp kreyvium.out
    
That's all folks!
