enum NetCommandType {NONE, PLAY, STOP, REG};

struct NetCommand
{
    NetCommandType type;
    char name[MAX_STR_LEN];
    int hz;
    int durationMs;
};

struct NetBuffer
{
    char data[MAX_NET_DATA_SIZE];
    int size;

    void consume(int n);
};

bool readInt(NetBuffer* netBuffer, int pos, int *res)
{
    if (pos + 3 >= netBuffer->size) {
        return false;
    }
    *res = 0;
    for (int i = 0; i < 4; i++) {
        *res = *res * 256 + netBuffer[pos + i];
    }
    return true;
}

int putInt(int x, char* dest)
{
    for (int i = 0; i < 4; i++)
    {
        dest[i] = (x >> (3 - i) * 8) & 255;
    }
    return 4;
}


NetCommand readNextCommand(NetBuffer* netBuffer)
{
    NetCommand result;
    char s = netBuffer->data[0];
    if (s == '1')
    {
        int hz, dur;
        if (readInt(netBuffer, 1, &hz) && readInt(netBuffer, 5, &dur)) {
            result.type = PLAY;
            result.hz = hz;
            result.durationMs = dur;
            netBuffer->consume(9);
            return result;
        }
    } else if (s == '2')
    {
        result.type = STOP;
        netBuffer->consume(1);
        return result;
    } else if (s == '3')
    {
        int len = 0;
        if (readInt(netBuffer, 1, &len))
        {
            if (5 + len <= netBuffer->size) {
                for (int i = 0; i < len; i++)
                {
                    result.name[i] = netBuffer->data[5 + i];
                }
                result.name[len] = 0;
                result.type = REG;
                netBuffer->consume(len + 5);
                return result;
            }
        }
    }
    result.type = NONE;
    return result;
}

int putCommand(NetCommand command, char* dest)
{
    if (command.type == PLAY)
    {
        dest[0] = '1';
        int a = putInt(command.hz, dest + 1);
        putInt(command.durationMs, dest + a + 1);
        return 1 + 2 * a;
    } else if (command.type == STOP)
    {
        dest[0] = '2';
        return 1;
    } else if (command.type == REG)
    {
        dest[0] = '3';
        /////////
    }

}
