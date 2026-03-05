import os
import mmap

class DMXUniverse:
    """Shared DMX-512 universe backed by a memory-mapped file (MAP_SHARED)."""
    
    DEFAULT_UNIVERSE = 0
    
    def __init__(self, universe=None):
        self.universe = universe if universe is not None else self.DEFAULT_UNIVERSE
        self.path = os.path.expanduser(f"~/.dmx/universe{self.universe}")
        self._open_file()
    
    def _open_file(self):
        os.makedirs(os.path.dirname(self.path), exist_ok=True)
        
        # Open the file read/write, create if missing, ensure 513 bytes
        fd = os.open(self.path, os.O_RDWR | os.O_CREAT, 0o666)
        try:
            # Check size
            current_size = os.path.getsize(self.path)
            if current_size < 513:
                os.lseek(fd, 0, os.SEEK_END)
                os.write(fd, bytes(513 - current_size))
            # mmap with MAP_SHARED semantics
            self.mmap = mmap.mmap(fd, 513, access=mmap.ACCESS_WRITE)
        finally:
            os.close(fd)  # fd is closed here; mmap remains valid
    
    def __getitem__(self, key):
        if isinstance(key, int):
            if not (1 <= key <= 512):
                raise IndexError("Channel must be 1..512")
            return self.mmap[key]
        elif isinstance(key, slice):
            start, stop, step = key.indices(513)
            return tuple(self.mmap[i] for i in range(start, stop, step))
        else:
            raise TypeError("Index must be int or slice")
    
    def __setitem__(self, key, value):
        if isinstance(key, int):
            if not (1 <= key <= 512):
                raise IndexError("Channel must be 1..512")
            if not (0 <= value <= 255):
                raise ValueError("DMX value must be 0..255")
            self.mmap[key] = value
        elif isinstance(key, slice):
            start, stop, step = key.indices(513)
            values = list(value)
            if len(values) != len(range(start, stop, step)):
                raise ValueError("Slice length mismatch")
            for i, v in zip(range(start, stop, step), values):
                if not (0 <= v <= 255):
                    raise ValueError("DMX values must be 0..255")
                self.mmap[i] = v
        else:
            raise TypeError("Index must be int or slice")
    
    def set_rgb(self, base, r, g, b):
        self[base:base+3] = (r, g, b)
    
    def close(self):
        """Close mmap (memory remains shared; no disk flush required)."""
        self.mmap.close()
