package alsa.entity.part;

public class Memory extends ComputerPart {

    private final int capacity;

    public Memory(int capacity) {
        this.capacity = capacity;
    }

    public int capacity() {
        return capacity;
    }

    @Override
    public String toString() {
        return "Memory{" +
                "capacity=" + capacity +
                '}';
    }
}
