#!/bin/bash

grep -io ei mobs.txt | wc -l
sed 's/ei/EI/gi' mobs.txt > MOBS.txt