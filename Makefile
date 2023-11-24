.PHONY: build
build:
	ninja -C build/

.PHONY: test
test:
	ninja -C build test

.PHONY: run_test
run_test:
	./build/test/copypp_test
	
.PHONY: run_test2
run_test2:
	./build/test/copypp_test2