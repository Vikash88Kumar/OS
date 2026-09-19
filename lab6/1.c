#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 100
#define MAX_FRAMES 20

void print_step(int step, int page, int frames[], int capacity, const char *status) {
    printf("%-6d %-6d [", step, page);
    for (int i = 0; i < capacity; i++) {
        if (frames[i] != -1)
            printf("%2d", frames[i]);
        else
            printf(" -");
        if (i < capacity - 1)
            printf(" | ");
    }
    printf("]  %s\n", status);
}

void fifo(int pages[], int n, int capacity) {
    printf("\n=============================================\n");
    printf(" FIFO (First-In, First-Out) Page Replacement\n");
    printf("=============================================\n");
    printf("%-6s %-6s %-18s %s\n", "Step", "Page", "Frames", "Status");
    printf("---------------------------------------------\n");

    int frames[MAX_FRAMES];
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    int faults = 0;
    int insert_ptr = 0; // Points to the oldest inserted frame position

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool hit = false;

        // Check for Page Hit
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                hit = true;
                break;
            }
        }

        if (hit) {
            print_step(i + 1, page, frames, capacity, "Hit");
        } else {
            faults++;
            frames[insert_ptr] = page;
            insert_ptr = (insert_ptr + 1) % capacity; // Circular replacement
            print_step(i + 1, page, frames, capacity, "Fault");
        }
    }

    printf("---------------------------------------------\n");
    printf("Total Page Faults: %d\n", faults);
    printf("Total Page Hits:   %d\n", n - faults);
}

void lru(int pages[], int n, int capacity) {
    printf("\n=============================================\n");
    printf(" LRU (Least Recently Used) Page Replacement\n");
    printf("=============================================\n");
    printf("%-6s %-6s %-18s %s\n", "Step", "Page", "Frames", "Status");
    printf("---------------------------------------------\n");

    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int hit_index = -1;

        // Check for Page Hit
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                hit_index = j;
                break;
            }
        }

        if (hit_index != -1) {
            last_used[hit_index] = i;
            print_step(i + 1, page, frames, capacity, "Hit");
        } else {
            faults++;
            int replace_idx = -1;

            // 1. Check if an empty frame is available
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
            }

            // 2. If all frames full, select the frame with minimum last_used value
            if (replace_idx == -1) {
                int min_time = last_used[0];
                replace_idx = 0;
                for (int j = 1; j < capacity; j++) {
                    if (last_used[j] < min_time) {
                        min_time = last_used[j];
                        replace_idx = j;
                    }
                }
            }

            frames[replace_idx] = page;
            last_used[replace_idx] = i;
            print_step(i + 1, page, frames, capacity, "Fault");
        }
    }

    printf("---------------------------------------------\n");
    printf("Total Page Faults: %d\n", faults);
    printf("Total Page Hits:   %d\n", n - faults);
}

void optimal(int pages[], int n, int capacity) {
    printf("\n=============================================\n");
    printf(" Optimal Page Replacement\n");
    printf("=============================================\n");
    printf("%-6s %-6s %-18s %s\n", "Step", "Page", "Frames", "Status");
    printf("---------------------------------------------\n");

    int frames[MAX_FRAMES];
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    int faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool hit = false;

        // Check for Page Hit
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                hit = true;
                break;
            }
        }

        if (hit) {
            print_step(i + 1, page, frames, capacity, "Hit");
        } else {
            faults++;
            int replace_idx = -1;

            // 1. Find an empty frame if present
            for (int j = 0; j < capacity; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
            }

            // 2. If full, find the page not used for the longest future duration
            if (replace_idx == -1) {
                int furthest_idx = -1;

                for (int j = 0; j < capacity; j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == frames[j]) {
                            next_use = k;
                            break;
                        }
                    }

                    // If a page is never referenced again, evict it immediately
                    if (next_use == -1) {
                        replace_idx = j;
                        break;
                    }

                    if (next_use > furthest_idx) {
                        furthest_idx = next_use;
                        replace_idx = j;
                    }
                }
            }

            frames[replace_idx] = page;
            print_step(i + 1, page, frames, capacity, "Fault");
        }
    }

    printf("---------------------------------------------\n");
    printf("Total Page Faults: %d\n", faults);
    printf("Total Page Hits:   %d\n", n - faults);
}

int main() {
    int n, capacity;
    int pages[MAX_PAGES];

    printf("Enter number of page references: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    if (scanf("%d", &capacity) != 1 || capacity <= 0) return 1;

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);

    return 0;
}