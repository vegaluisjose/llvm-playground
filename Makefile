EMBENCH_DIR = $(abspath .)/3rdparty/embench-iot
CFLAGS = -I$(EMBENCH_DIR)/support -DCPU_MHZ=1
BUILD_DIR = $(abspath .)/build

NAME = matmult-int
PASS_LIB = $(BUILD_DIR)/pass/hello/libHelloPass.so
PASS_NAME = hello

default: run_pass

$(BUILD_DIR):
	mkdir -p $@

$(PASS_LIB): | $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make && cd ..

$(BUILD_DIR)/$(NAME).ll: | $(BUILD_DIR)
	clang $(CFLAGS) -emit-llvm -Xclang -disable-O0-optnone -S $(EMBENCH_DIR)/src/$(NAME)/$(NAME).c -o $@

run_pass: $(PASS_LIB) $(BUILD_DIR)/$(NAME).ll
	opt -load $(PASS_LIB) -$(PASS_NAME) < $(BUILD_DIR)/$(NAME).ll > /dev/null

clean:
	rm -rf $(BUILD_DIR)
