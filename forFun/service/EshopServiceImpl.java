package alsa.service;

import alsa.entity.Product;
import alsa.persistence.Database;

import java.util.*;

public class EshopServiceImpl implements EshopService {

    private final Database database;

    public EshopServiceImpl(Database database) {
        this.database = database;
    }

    public List<Product> getProducts() {
        return database.findProducts();
    }

    public List<Product> getProducts(Comparator<Product> productComparator) {
        List<Product> products = new ArrayList<>(database.findProducts());
        Collections.sort(products, productComparator);
        return products;
    }

    public void addProductToStorage(Product product) {
        database.saveProduct(product);
    }

    public void addProductsToStorage(Product... products) {
        for (Product product : products) {
            addProductToStorage(product);
        }
    }

    public boolean sellProduct(String name) {
        Optional<Product> oProduct = database.findProductByName(name);

        if (!oProduct.isPresent()) {
            return false;
        }
        Product product = oProduct.get();

        if (product.count() == 0) {
            return false;
        }

        Product updatedProduct = product.decreaseCount();
        database.saveProduct(updatedProduct);
        return true;
    }

    public boolean returnProduct(String name) {
        Optional<Product> oProduct = database.findProductByName(name);

        if (!oProduct.isPresent()) {
            return false;
        }
        Product product = oProduct.get();

        if (!product.hasSpecialGuarantee()) {
            return false;
        }

        Product updatedProduct = product.increaseCount();
        database.saveProduct(updatedProduct);
        return true;
    }

}
