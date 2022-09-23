NAME = cipherlib.a
CC = gcc
C_SRC = $(wildcard src/**/*.c)
C_OBJ = $(C_SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -Iinc -maes -mrdrnd
UNIT_SRC = $(wildcard test/*.c)
UNIT_OBJ = $(UNIT_SRC:.c=)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -O3 -m64 -c $< -o $@

$(NAME): $(C_OBJ)
	ar rcs $(NAME) $(C_OBJ)

clean:
	rm -rf $(C_OBJ)

unit: $(NAME)
	$(CC) -Iinc test/hex_encoder.c cipherlib.a -O3 -o test/hex_encoder 
	$(CC) -Iinc test/hex_decoder.c cipherlib.a -O3 -o test/hex_decoder
	$(CC) -Iinc test/base64_encoder.c cipherlib.a -O3 -o test/base64_encoder
	$(CC) -Iinc test/base64_decoder.c cipherlib.a -O3 -o test/base64_decoder
	$(CC) -Iinc test/utils.c cipherlib.a -O3 -o test/utils
	$(CC) -Iinc test/prng.c cipherlib.a -O3 -o test/prng
	$(CC) -Iinc test/simple_xor.c cipherlib.a -O3 -o test/simple_xor
	$(CC) -Iinc test/xor_128.c cipherlib.a -O3 -o test/xor_128
	$(CC) -Iinc test/aes_key_schedule.c cipherlib.a -O3 -o test/aes_key_schedule
	$(CC) -Iinc test/aes_128_enc_dec.c cipherlib.a -O3 -o test/aes_128_enc_dec
	$(CC) -Iinc test/pkcs7_test.c cipherlib.a -O3 -o test/pkcs7_test

unit_clean: $(UNIT_OBJ)
	rm -rf $(UNIT_OBJ)
	
fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
