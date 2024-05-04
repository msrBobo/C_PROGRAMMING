#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define BLOCKCHAIN_FILENAME "blockchain.txt"

#define MAX_NODES 1024
#define MAX_BLOCKS 1024

typedef struct Block {
    char* bid;
    struct Block* next;
} Block;

typedef struct Node {
    int nid;
    Block* blockList;
    struct Node* next;
} Node;

int add_Node(int nid, Node** blockchain);
int remove_Node(int nid, Node** blockchain);
int add_Block(char* bid, int nid, Node* blockchain);
int remove_Block(char* bid, Node* blockchain);
void print_Nodes(Node* blockchain, int listBlocks);
void sync_Nodes(Node* blockchain);
void save_Blockchain(Node* blockchain);
Node* load_Blockchain();
int count_Nodes(Node* blockchain);
bool check_Sync_State(Node* blockchain);
void free_Nodes(Node* blockchain);
void process_Add_Command(char* arg1, char* arg2, char* arg3, Node** blockchain);
void process_Rm_Command(char* arg1, char* arg2, Node** blockchain);
void process_Ls_Command(char* arg1, Node* blockchain);
void process_Sync_Command(Node* blockchain);
void my_Blockchain();

#endif


