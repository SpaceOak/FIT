package alsa.persistence;

import alsa.entity.Product;

import java.util.Collections;
import java.util.List;
import java.util.Optional;

public interface Database {

    List<Product> findProducts();

    Optional<Product> findProductByName(String name);

    void saveProduct(Product product);

    void removeProduct(Product product);

    public static final Database DUMMY_DATABASE = new Database() {
        @Override
        public List<Product> findProducts() {
            return Collections.emptyList();
        }

        @Override
        public Optional<Product> findProductByName(String name) {
            return Optional.empty();
        }

        @Override
        public void saveProduct(Product product) {

        }

        @Override
        public void removeProduct(Product product) {

        }
    };

}
