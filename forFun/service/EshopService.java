package alsa.service;

import alsa.entity.Product;

import java.util.Comparator;
import java.util.List;

public interface EshopService {

    List<Product> getProducts();

    List<Product> getProducts(Comparator<Product> productComparator);

    void addProductToStorage(Product product);

    void addProductsToStorage(Product... products);

    boolean sellProduct(String name);

    boolean returnProduct(String name);

}
