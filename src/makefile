CLIENT_DIR=client
SERVER_DIR=server
BUILD_DIR=../build
TIMEOUT=10
VALGRIND=valgrind --leak-check=yes --error-exitcode=1

.PHONY: default all clean format client server test

default: all

all:
	cd $(CLIENT_DIR) && make
	cd $(SERVER_DIR) && make

run: all
	$(BUILD_DIR)/tp2_server & $(BUILD_DIR)/tp2_client
run_timed: all
	(timeout $(TIMEOUT) $(BUILD_DIR)/tp2_server) & (timeout $(TIMEOUT) $(BUILD_DIR)/tp2_client)

format: 
	cd $(CLIENT_DIR) && make format
	cd $(SERVER_DIR) && make format

$(BUILD_DIR)/tp2_client:
	cd $(CLIENT_DIR) && make

$(BUILD_DIR)/tp2_server:
	cd $(SERVER_DIR) && make

client: $(BUILD_DIR)/tp2_client
server: $(BUILD_DIR)/tp2_server

clean:
	cd $(CLIENT_DIR) && make clean
	cd $(SERVER_DIR) && make clean
	rm -f *.log *.aux *.pdf

rapport: rapport.tex
	pdflatex rapport.tex

valgrind: $(BUILD_DIR)/tp2_client $(BUILD_DIR)/tp2_server
	$(VALGRIND) $(BUILD_DIR)/tp2_server &> /dev/null & $(VALGRIND) $(BUILD_DIR)/tp2_client &> /dev/null
	$(VALGRIND) $(BUILD_DIR)/tp2_client &> /dev/null & $(VALGRIND) $(BUILD_DIR)/tp2_server &> /dev/null

release: rapport valgrind clean format
	tar -czvf ../tp2.tar.gz . 
