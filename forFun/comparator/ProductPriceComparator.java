package alsa.comparator;

import alsa.entity.Product;

import java.util.Comparator;

public class ProductPriceComparator implements Comparator<Product> {

    private final SortOrder sortOrder;

    public ProductPriceComparator(SortOrder sortOrder) {
        this.sortOrder = sortOrder;
    }

    public int compare(Product o1, Product o2) {
        int result = Double.compare(o1.price(), o2.price());
        return sortOrder == SortOrder.ASCENDING ? result : -result;
    }

}
