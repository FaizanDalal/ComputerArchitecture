#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct inst {
    char operation[20];
    int n;
    int s;
    int *inputs;
    int *outputs;
    int *selectors;
}inst;

void NOT(int *values, int inputIndex, int outputIndex) {
    values[outputIndex] = !values[inputIndex];
}

void AND(int *values, int inputIndex1, int inputIndex2, int outputIndex) {
    values[outputIndex] = values[inputIndex2] && values[inputIndex1];
}

void OR(int *values, int inputIndex1, int inputIndex2, int outputIndex) {
    values[outputIndex] = values[inputIndex2] || values[inputIndex1];
}

void NAND(int *values, int inputIndex1, int inputIndex2, int outputIndex) {
    values[outputIndex] = !(values[inputIndex2] && values[inputIndex1]);
}

void NOR(int *values, int inputIndex1, int inputIndex2, int outputIndex) {
    values[outputIndex] = !(values[inputIndex2] || values[inputIndex1]);
}

void XOR(int *values, int inputIndex1, int inputIndex2, int outputIndex) {
    values[outputIndex] = values[inputIndex2] ^ values[inputIndex1];
}
int power(int base, int power)
    {
      if(power < 0)
        return -1;

        int result = 1;
        while (power)
        {
            if (power & 1)
                result *= base;
            power >>= 1;
            base *= base;
        }

        return result;
    }
void DECODER(int *values, int n, int *inputIndex, int *outputIndex) {
    int s = 0;
    int i = 0;
    for (i = 0; i < power(2, n); i++) {
        values[outputIndex[i]] = 0;
    }
    for (i = 0; i < n; i++) {
        s = s + values[inputIndex[i]] * power(2, n - i - 1);
    }
    values[outputIndex[s]] = 1;
}

void MULTIPLEXER(int *values, int n, int *inputIndex, int *selectionIndex, int outputIndex) {
    int s = 0;
    int i;
    for (i = 0; i < n; i++) {
        s = s + values[selectionIndex[i]] * power(2, n - i - 1);
    }
    values[outputIndex] = values[inputIndex[s]];
}
void PASS(int *values, int inputIndex, int outputIndex) {
    values[outputIndex] = values[inputIndex];
}

int indexOf(int size, char **arr, char *var) {
    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(arr[i], var) == 0) {
            return i;
        }
    }
    return -1;
}

void resetValues(int size, int *arr) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = 0;
    }
    arr[1] = 1;
}
int incrementInputs(int *arr, int indexCount) {
    int i;
    for (i = indexCount + 1; i >= 2; i--) {
        arr[i] = !arr[i];
        if (arr[i] == 1) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
	FILE *file = fopen(argv[1], "r");
   if (argc < 2)
    {
        return 0;
    }
    if (file == NULL)
    {
        return 0;
    }

    int scount = 0;
    struct inst* steps = NULL;
    int size = 2;
    int indexCount = 0;
    int outputCount = 0;
    int tcount = 0;
    char dir[20];
    char **names;
    int *values = malloc(size * sizeof(int));
    fscanf(file, " %s", dir);
    fscanf(file, "%d", &indexCount);

    size += indexCount;
    names = malloc(size * sizeof(char *));
    names[0] = malloc(2 * sizeof(char));
    names[0] = "0\0";
    names[1] = malloc(2 * sizeof(char));
    names[1] = "1\0";

    int i;
    for (i = 0; i < indexCount; i++) {
        names[i + 2] = malloc(20 * sizeof(char));
        fscanf(file, "%16s", names[i + 2]);
    }

    
    fscanf(file, " %s", dir);
    fscanf(file, "%d", &outputCount);
    size += outputCount;
    names = realloc(names, size * sizeof(char *));
    for (i = 0; i < outputCount; i++) {
        names[i + indexCount + 2] = malloc(20 * sizeof(char));
        fscanf(file, "%16s", names[i + indexCount + 2]);
    }

    while (!feof(file)) {
        int numInputs = 2, numOutputs = 1;
        struct inst step;
        int sc = fscanf(file, " %s", dir); 
        if (sc != 1) {
        	break;     
        }

        scount++;
        step.n = 0;
        step.s = 0;
        strcpy(step.operation, dir);

        if (strcmp(dir, "NOT") == 0) {
            numInputs = 1;
        }
        if (strcmp(dir, "PASS") == 0) {
            numInputs = 1;
        }
        if (strcmp(dir, "DECODER") == 0) {
            fscanf(file, "%d", &numInputs);
            step.n = numInputs;
            numOutputs = power(2, numInputs);
        }
        if (strcmp(dir, "MULTIPLEXER") == 0) {
            fscanf(file, "%d", &numInputs);
            step.s = numInputs;
            numInputs = power(2, numInputs);
        }

        step.inputs = malloc(numInputs * sizeof(int));
        step.outputs = malloc(numOutputs * sizeof(int));
        step.selectors = malloc(step.s * sizeof(int));

        char v[20];
        for (i = 0; i < numInputs; i++) {
            fscanf(file, "%16s", v);
            step.inputs[i] = indexOf(size, names, v);
        }

        for (i = 0; i < step.s; i++) {
            fscanf(file, "%16s", v);
            step.selectors[i] = indexOf(size, names, v);
        }
 
        for (i = 0; i < numOutputs; i++) {
            fscanf(file, "%16s", v);
            int idx = indexOf(size, names, v);
            if (idx != -1) {
            step.outputs[i] = idx;
            }
            else {
            	size++;
                tcount++;
                names = realloc(names, size * sizeof(char *));
                names[size - 1] = malloc(20 * sizeof(char));
                strcpy(names[size - 1], v);
                step.outputs[i] = size - 1;
            }
        }
        if (steps != NULL) {
            steps = realloc(steps, scount * sizeof(struct inst));

        } else {
            steps = malloc(sizeof(struct inst));

        }
        steps[scount - 1] = step;
    }
    values = malloc(size * sizeof(int));
    resetValues(size, values);

    while(1 < 2) {
        

        for (i = 0; i < scount; i++) {
            struct inst step = steps[i];
            if (strcmp(step.operation, "NOT") == 0) {
                NOT(values, step.inputs[0], step.outputs[0]);
            }
            if (strcmp(step.operation, "AND") == 0) {
                AND(values, step.inputs[0], step.inputs[1], step.outputs[0]);
            }
            if (strcmp(step.operation, "OR") == 0) {
                OR(values, step.inputs[0], step.inputs[1], step.outputs[0]);
            }
            if (strcmp(step.operation, "NAND") == 0) {
                NAND(values, step.inputs[0], step.inputs[1], step.outputs[0]);
            }
            if (strcmp(step.operation, "NOR") == 0) {
                NOR(values, step.inputs[0], step.inputs[1], step.outputs[0]);
            }
            if (strcmp(step.operation, "XOR") == 0) {
                XOR(values, step.inputs[0], step.inputs[1], step.outputs[0]);
            }
            if (strcmp(step.operation, "DECODER") == 0) {
                DECODER(values, step.n, step.inputs, step.outputs);
            }
            if (strcmp(step.operation, "MULTIPLEXER") == 0) {
                MULTIPLEXER(values, step.s, step.inputs, step.selectors, step.outputs[0]);
            }
            if (strcmp(step.operation, "PASS") == 0) {
                PASS(values, step.inputs[0], step.outputs[0]);
            }
        }
        for (i = 0; i < indexCount; i++) {
            printf("%d ", values[i + 2]);
        }
        printf("|");

        for (i = 0; i < outputCount; i++) {
            printf(" %d", values[indexCount + i + 2]);
        }
        printf("\n");

        if (incrementInputs(values, indexCount)) {
            continue;
        }
        else{
        	break;
        }
    }

    return 0;
}