package alsa.entity;

import alsa.entity.part.ComputerPart;

public class Notebook extends Product {

    private final NotebookCategory category;

    private final ComputerPart[] computerParts;

    public Notebook(String name, double price, int count, NotebookCategory category, ComputerPart[] computerParts) {
        super(name, price, count);
        this.category = category;
        this.computerParts = computerParts;
    }

    public NotebookCategory category() {
        return category;
    }

    public ComputerPart[] computerParts() {
        return computerParts;
    }

    @Override
    public Notebook increaseCount() {
        return new Notebook(name, price, count + 1, category, computerParts);
    }

    @Override
    public Notebook decreaseCount() {
        return new Notebook(name, price, count - 1, category, computerParts);
    }

    @Override
    public boolean hasSpecialGuarantee() {
        return true;
    }

    @Override
    public String toString() {
        return "Notebook{" +
                "category=" + category +
                ", computerParts=" + computerParts +
                ", name='" + name + '\'' +
                ", price=" + price +
                ", count=" + count +
                '}';
    }
}
