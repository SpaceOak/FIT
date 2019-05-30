package alsa.persistence;

import alsa.entity.Product;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class InMemoryDatabase implements Database {

    private final List<Product> products = new ArrayList<>();

    public List<Product> findProducts() {
        return products;
    }

    public Optional<Product> findProductByName(String name) {
        for (Product product : products) {
            if (product.name().equals(name)) {
                return Optional.of(product);
            }
        }
        return Optional.empty();
    }

    public void saveProduct(Product product) {
        products.removeIf(productInDb -> productInDb.name().equals(product.name()));
        products.add(product);
    }

    public void removeProduct(Product product) {
        products.remove(product);
    }
}
