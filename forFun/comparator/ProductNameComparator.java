package alsa.comparator;

import alsa.entity.Product;

import java.util.Comparator;

public class ProductNameComparator implements Comparator<Product> {

    private final SortOrder sortOrder;

    public ProductNameComparator(SortOrder sortOrder) {
        this.sortOrder = sortOrder;
    }

    public int compare(Product o1, Product o2) {
        int result = o1.name().compareTo(o2.name());
        return sortOrder == SortOrder.ASCENDING ? result : -result;
    }

}
