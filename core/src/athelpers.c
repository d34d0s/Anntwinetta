#define STB_IMAGE_IMPLEMENTATION
#include "../headers/athelpers.h"

// File manipulation helpers
char* atReadFile(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        atLogError("ReadFile :: UNABLE TO ACCESS FILE");
        return NULL;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        atLogError("ReadFile :: UNABLE TO SEEK IN FILE");
        fclose(file );
        return NULL;
    }

    long len = ftell(file);
    if (len == -1) {
        atLogError("ReadFile :: UNABLE TO DETERMINE SIZE OF FILE");
        fclose(file);
        return NULL;
    }
    rewind(file);

    char *fileContent = malloc(len+1);
    if (fileContent == NULL) {
        atLogError("ReadFile :: MEMORY ALLOCATION]");
        return NULL;
    }

    size_t readSize = fread(fileContent, 1, len, file);
    if (readSize < (size_t)len) {
        atLogError("ReadFile :: UNABLE TO READ FILE :: READ [%zu/%ld]", readSize, len);
        return NULL;
    }
    fileContent[len] = '\0';
    fclose(file);

    return fileContent;
}


// ARRAY INITIALIZATION
int atInitIntArray(int** array, unsigned int size, const char* fieldName) {
    *array = (int*)malloc(sizeof(int) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    return 0;
}

int atInitIntPointerArray(int*** array, unsigned int size, unsigned int size2, const char* fieldName) {
    *array = (int**)malloc(sizeof(int*) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    for (int i = 0; i < size; i++) {
        (*array)[i] = (int*)malloc(sizeof(int) * size2);
        if ((*array)[i] == NULL) {
            atLogError("Error Allocating Space For Field: %s", fieldName);
            return 1;
        }
    }
    return 0;
}


int atInitConstCharArray(const char** array, unsigned int size, const char* fieldName) {
    *array = (const char*)malloc(sizeof(const char) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    return 0;
}

int atInitConstCharPointerArray(const char*** array, unsigned int size, unsigned int size2, const char* fieldName) {
    *array = (const char**)malloc(sizeof(const char*) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    for (int i = 0; i < size; i++) {
        (*array)[i] = (const char*)malloc(sizeof(const char) * size2);
        if ((*array)[i] == NULL) {
            atLogError("Error Allocating Space For Field: %s", fieldName);
            return 1;
        }
    }
    return 0;
}

int atInitCharArray(char** array, unsigned int size, const char* fieldName) {
    *array = (char*)malloc(sizeof(char) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    return 0;
}

int atInitCharPointerArray(char*** array, unsigned int size, unsigned int size2, const char* fieldName) {
    *array = (char**)malloc(sizeof(char*) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    for (int i = 0; i < size; i++) {
        (*array)[i] = (char*)malloc(sizeof(char) * size2);
        if ((*array)[i] == NULL) {
            atLogError("Error Allocating Space For Field: %s", fieldName);
            return 1;
        }
    }
    return 0;
}


int atArray(float** array, unsigned int size, const char* fieldName) {
    *array = (float*)malloc(sizeof(float) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    return 0;
}

int atPointerArray(float*** array, unsigned int size, unsigned int size2, const char* fieldName) {
    *array = (float**)malloc(sizeof(float*) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    for (int i = 0; i < size; i++) {
        (*array)[i] = (float*)malloc(sizeof(float) * size2);
        if ((*array)[i] == NULL) {
            atLogError("Error Allocating Space For Field: %s", fieldName);
            return 1;
        }
    }
    return 0;
}


int atInitUnsignedIntArray(unsigned int** array, unsigned int size, const char* fieldName) {
    *array = (unsigned int*)malloc(sizeof(unsigned int) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    return 0;
}

int atInitUnsignedIntPointerArray(unsigned int*** array, unsigned int size, unsigned int size2, const char* fieldName) {
    *array = (unsigned int**)malloc(sizeof(unsigned int*) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    for (int i = 0; i < size; i++) {
        (*array)[i] = (unsigned int*)malloc(sizeof(unsigned int) * size2);
        if ((*array)[i] == NULL) {
            atLogError("Error Allocating Space For Field: %s", fieldName);
            return 1;
        }
    }
    return 0;
}


int atInitVoidArray(void** array, unsigned int size, const char* fieldName) {
    *array = malloc(sizeof(void*) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    return 0;
}

int atInitVoidPointerArray(void*** array, unsigned int size, unsigned int size2, const char* fieldName) {
    *array = (void**)malloc(sizeof(void*) * size);
    if (*array == NULL) {
        atLogError("Error Allocating Space For Field: %s", fieldName);
        return 1;
    }
    for (unsigned int i = 0; i < size; i++) {
        (*array)[i] = malloc(sizeof(void*) * size2);
        if ((*array)[i] == NULL) {
            atLogError("Error Allocating Space For Field: %s", fieldName);
            return 1;
        }
    }
    return 0;
}
