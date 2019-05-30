package alsa.entity;

public class Television extends Product {

    public Television(String name, double price, int count) {
        super(name, price, count);
    }

    @Override
    public Television increaseCount() {
        return new Television(name, price, count + 1);
    }

    @Override
    public Television decreaseCount() {
        return new Television(name, price, count - 1);
    }

    @Override
    public boolean hasSpecialGuarantee() {
        return false;
    }


    @Override
    public String toString() {
        return "Television{" +
                "name='" + name + '\'' +
                ", price=" + price +
                ", count=" + count +
                '}';
    }
}
