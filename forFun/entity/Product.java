package alsa.entity;

public abstract class Product {

    protected final String name;

    protected final double price;

    protected final int count;

    public Product(String name, double price, int count) {
        this.name = name;
        this.price = price;
        this.count = count;
    }

    public String name() {
        return name;
    }

    public double price() {
        return price;
    }

    public int count() {
        return count;
    }

    public abstract Product increaseCount();

    public abstract Product decreaseCount();

    public abstract boolean hasSpecialGuarantee();

    @Override
    public String toString() {
        return "Product{" +
                "name='" + name + '\'' +
                ", price=" + price +
                ", count=" + count +
                '}';
    }
}
