void insertionSort(int *data, int start, int end)
{
    for (int i = start + 1; i <= end; i++)
    {
        int index = i - 1;
        while(index >= start && (data[index] > data[index + 1]))
        {
            data[index + 1] = data[index + 1] ^ data[index];
            data[index] = data[index] ^ data[index + 1];
            data[index + 1] = data[index + 1] ^ data[index];
            index--;
        }
    }
}

void smartQuickSort(int *data, int start, int end) {
    if (start >= end) {
        return;
    }

    if (end - start + 1 <= 10) {
        insertionSort(data, start, end);
        return;
    }

    int bound = data[(start + end) / 2];
    int left = start;
    int right = end;

    while (left <= right) {
        while (data[left] < bound) {
            ++left;
        }
        while (data[right] > bound && (right > 0)) {
            --right;
        }
        if (left <= right) {
            if (data[left] != data[right]){
                data[left] = data[left] ^ data[right];
                data[right] = data[right] ^ data[left];
                data[left] = data[left] ^ data[right];
            }
            ++left;
            --right;
        }
    }
    smartQuickSort(data, start, right);
    smartQuickSort(data, left, end);
}

int main() {
    return 0;
}

