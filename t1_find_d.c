/* bn_sample.c */
#include <stdio.h>
#include <openssl/bn.h>
#define NBITS 256

//p = F7E75FDC469067FFDC4E847C51F452DF 
//q = E85CED54AF57E53E092113E62F436F4F 
//e = 0D88C3

void printBN(char *msg, BIGNUM * a)
{
/* Use BN_bn2hex(a) for hex string
* Use BN_bn2dec(a) for decimal string */
char * number_str = BN_bn2hex(a);
printf("%s %s\n", msg, number_str);
OPENSSL_free(number_str);
}

int main ()
{
	//BN_CTX *ctx = BN_CTX_new();
	//BIGNUM *a = BN_new();
	//BIGNUM *b = BN_new();
	//BIGNUM *n = BN_new();
	//BIGNUM *res = BN_new();
	//// Initialize a, b, n
	//BN_generate_prime_ex(a, NBITS, 1, NULL, NULL, NULL);
	//BN_dec2bn(&b, "273489463796838501848592769467194369268");
	//BN_rand(n, NBITS, 0, 0);
	//// res = a*b
	//BN_mul(res, a, b, ctx);
	//printBN("a * b = ", res);
	//// res = aˆb mod n
	//BN_mod_exp(res, a, b, n, ctx);
	//printBN("aˆc mod n = ", res);
	//return 0;

	//p = F7E75FDC469067FFDC4E847C51F452DF 
	//q = E85CED54AF57E53E092113E62F436F4F 
	//e = 0D88C3

	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *o   = BN_new(); //1
	BIGNUM *p   = BN_new();
	BIGNUM *pmo = BN_new(); // p - 1
	BIGNUM *q   = BN_new();
	BIGNUM *qmo = BN_new(); // q - 1
	BIGNUM *e   = BN_new();
	BIGNUM *d   = BN_new();
	BIGNUM *phi = BN_new(); // (p - 1) (q - 1)

 printf("Task 1: find d\n");
	BN_hex2bn(&o, "1");
	BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
	BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
	BN_hex2bn(&e, "0D88C3");
 BN_sub(pmo, p, o);
 BN_sub(qmo, q, o);
 BN_mul(phi, pmo, qmo, ctx);
	printBN("(p - 1)*(q - 1) = ", phi);
 BN_mod_inverse(d, e, phi, ctx);
	printBN("d = ", d);
	return 0;
}

