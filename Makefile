all: run

run: pdsp_dp
	./pdsp_dp

pdsp_dp: pdsp_dp.c pdsp_dp_test.c
	gcc -Wall -o $@ $^

clean:
	rm -f pdsp_dp
