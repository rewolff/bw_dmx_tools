#!/usr/bin/env python3
import argparse
import time
from bw_dmx import DMXUniverse  # directly import the class

def main():
    parser = argparse.ArgumentParser(description="DMX single-channel sweep test")
    parser.add_argument("min", type=int, help="Minimum channel number (1..512)")
    parser.add_argument("max", type=int, help="Maximum channel number (1..512)")
    parser.add_argument("--delay", type=float, default=0.1,
                        help="Delay between channel moves in seconds")
    parser.add_argument("--universe", type=int, default=0,
                        help="DMX universe number (default 0)")
    args = parser.parse_args()

    if not (1 <= args.min <= 512) or not (1 <= args.max <= 512):
        print("Error: channels must be between 1 and 512")
        return
    if args.min >= args.max:
        print("Error: min must be less than max")
        return

    # Use the class directly
    uni = DMXUniverse(args.universe)
    current = args.min
    direction = 1  # 1 = up, -1 = down
    for ch in range(args.min, args.max + 1):
       uni[ch] = 0

    try:
        while True:
            # Turn on current channel
            uni[current] = 255
            time.sleep(args.delay)
            uni[current] = 0
            
            if current >= args.max:
                direction = -1
            elif current <= args.min:
                direction = 1

            # Move to next channel
            current += direction

    except KeyboardInterrupt:
        # Turn off all channels in range on exit
        for ch in range(args.min, args.max + 1):
            uni[ch] = 0
        uni.close()
        print("\nExiting bounce test.")

if __name__ == "__main__":
    main()
