=#include <stdio.h>
#define MAX_FRAMES 3
int main()
{
    int frames[MAX_FRAMES];
    int num_frames = 0;
    int page_faults = 0;
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }
    int page_reference[] = {4, 1, 2, 4, 3, 2, 1, 5};
    int num_pages = sizeof(page_reference) / sizeof(page_reference[0]);
    for (int i = 0; i < num_pages; i++) {
        int page = page_reference[i];
        int found = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (num_frames < MAX_FRAMES) {
                frames[num_frames++] = page;
            } else {
                for (int j = 0; j < MAX_FRAMES - 1; j++) {
                    frames[j] = frames[j+1];
                }
                frames[MAX_FRAMES - 1] = page;
            }
            page_faults++;
        }
        printf("Page %d: ", page);
        for (int j = 0; j < num_frames; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Number of page faults: %d\n", page_faults);
    return 0;
}


