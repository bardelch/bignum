#include <stdio.h>
#include <string.h>
#include <openssl/bn.h>

//https://www.includehelp.com/c/convert-ascii-string-to-hexadecimal-string-in-c.aspx#:~:text=Extract%20characters%20from%20the%20input,character%20to%20the%20output%20string.
//function to convert ascii char[] to hex-string (char[])
void string2hexString(char* input, char* output)
{
    int loop;
    int i; 
    
    i=0;
    loop=0;
    
    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}

//int main(){
//    char ascii_str[] = "Hello world!";
//    //declare output string with double size of input string
//    //because each character of input string will be converted
//    //in 2 bytes
//    int len = strlen(ascii_str);
//    char hex_str[(len*2)+1];
//    
//    //converting ascii string to hex string
//    string2hexString(ascii_str, hex_str);
//    
//    printf("ascii_str: %s\n", ascii_str);
//    printf("hex_str: %s\n", hex_str);
//    
//    return 0;
//}
//python -c ’print("A top secret!".encode("hex"))’ 
//4120746f702073656372657421
//n = DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5 
//e = 010001 (this hex value equals to decimal 65537) 
//M = A top secret! 
//d = 74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D

void printBN(char *msg, BIGNUM * a)
{
 /* Use BN_bn2hex(a) for hex string
 * Use BN_bn2dec(a) for decimal string */
 char * number_str = BN_bn2hex(a);
 printf("%s %s\n", msg, number_str);
 OPENSSL_free(number_str);
}

void printBNascii(char *msg, BIGNUM *a){
 char * hexStr = BN_bn2hex(a);
 unsigned short lenHex = strlen(hexStr);
 unsigned short lenChar = lenHex/2;
 char m[lenChar+1], hex[3];
 hex[2] = '\0';
 for(unsigned short i = 0; i < lenChar; ++i){
  hex[0] = hexStr[i*2];
  hex[1] = hexStr[i*2+1];
  m[i] = (char) strtoul(hex, NULL, 16);
 }
 OPENSSL_free(hexStr);
 printf("%s: '%s'\n", msg, m);
}

int main ()
{
 printf("Task 2: encrypt using key\n");
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *n = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *M = BN_new();
	BIGNUM *M2 = BN_new();
	BIGNUM *C = BN_new();
 char *m = "A top secret!";
 int lenM = strlen(m);
 char hexM[(lenM*2)+1];
 string2hexString(m, hexM);
 printf("ascii_str: %s\n", m);
 printf("hex_str: %s\n", hexM);

	BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&e, "010001");
	BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
	BN_hex2bn(&M, hexM);

	//// C = Mˆe mod n
 //Compute res = a^c mod n:
 //BN_mod_exp(res, a, c, n, ctx)
	//printBN("aˆc mod n = ", res);
 BN_mod_exp(C, M, e, n, ctx);
	printBN("Mˆe mod n = ", C);

 //// M = C^d mod n
 BN_mod_exp(M2, C, d, n, ctx);
 printBNascii("decrypted message", M2);


	return 0;
}

