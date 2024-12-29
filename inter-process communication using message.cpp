#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Define message structure
struct msg_buffer {
    long msg_type;  // Message type (1 for sender)
    char msg_text[100];  // Message content
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a unique key using ftok() function
    key = ftok("progfile", 65); 
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Send a message
    message.msg_type = 1; // Message type (1 for sender)
    printf("Enter message to send: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);
    message.msg_text[strcspn(message.msg_text, "\n")] = 0;  // Remove newline

    // Send the message to the queue
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent: %s\n", message.msg_text);

    return 0;
}


//reciever
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Define message structure
struct msg_buffer {
    long msg_type;  // Message type (1 for sender)
    char msg_text[100];  // Message content
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate the same key using ftok()
    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Receive a message from the queue
    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Message received: %s\n", message.msg_text);

    // Destroy the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    return 0;
}

