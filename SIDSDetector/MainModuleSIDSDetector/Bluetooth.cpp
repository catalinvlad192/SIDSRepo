#include "Bluetooth.h"

namespace mm{
Bluetooth::Bluetooth()
{}

void Bluetooth::communicateApl(const char* string, const char* abnormality1, const char* abnormality2) const
{
        Serial2.println("GB");
        Serial2.println(string);
        Serial2.println(abnormality1);
        Serial2.println(abnormality2);
        Serial2.println("OVR");
}

void Bluetooth::communicateDev(int* pulse, float* ox, float* temp, int* rem, char* prob) const
{
    char readData[100];
    char trimmedData[100];
    strcpy(readData, "");
    strcpy(trimmedData, "");

    // Read String
    while (Serial3.available() > 0)
    {
        char t = Serial3.read();
        strncat(readData, &t, 1);
    }

    Serial.println(readData);

    // After this we have content between SML and OVR
    const char* SML="SML\n";
    const char* OVR="\nOVR";

    char* aux = NULL;
    char* start, *end;
    if (start = strstr(readData, SML))
    {
        start += strlen(SML);
        if (end = strstr(start, OVR))
        {
            aux = (char*)malloc(end-start+1);
            memcpy(aux, start, end-start);
            aux[end - start] = '\0';
        }
    }
    if (aux) strcpy(trimmedData, aux);
    free(aux);

    // After this we have 2 strings: data and problems
    char* endlineToken;
    char splitData[2][50];
	strcpy(splitData[0], "");
	strcpy(splitData[1], "");
    int i=0;

    endlineToken = strtok(trimmedData, "\n");
    while (endlineToken != NULL)
    {
        if (i<2)
        {
            strcpy(splitData[i],endlineToken);
            i++;
        }
        endlineToken = strtok(NULL, "\n");
    }
    strcpy(prob, splitData[1]);

    // Process data
    char* spaceToken;
    int count = 0;

    spaceToken = strtok(splitData[0], " ");
    while (spaceToken != NULL)
    {
        if (count == 0)
        {
            int x = atoi(spaceToken);
            if (x >= 0 && x <= 300)
                *pulse = x;
            count++;
        }
        else if (count == 1)
        {
            float f = atof(spaceToken);
            if (f <= 100.0f && f >= 50)
                *ox = f;
            count++;
        }
        else if (count == 2)
        {
            float f = atof(spaceToken);
            if (f >= -1.0f && f <= 50.0f)
                *temp = f;
            count++;
        }
        else if (count == 3)
        {
            int x = atoi(spaceToken);
            if (x >= 0 && x <= 1)
                *rem = x;
            count++;
        }
        spaceToken = strtok(NULL, " ");
    }
}
} // namespace mm
