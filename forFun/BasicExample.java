package alsa;

import alsa.comparator.ProductNameComparator;
import alsa.comparator.ProductPriceComparator;
import alsa.comparator.SortOrder;
import alsa.entity.Product;
import alsa.persistence.InMemoryDatabase;
import alsa.service.EshopService;
import alsa.service.EshopServiceImpl;

import java.util.List;

import static alsa.SampleData.*;
import static alsa.util.ProductUtils.printProducts;

public class BasicExample {

    private static EshopService createEshop() {
        return new EshopServiceImpl(new InMemoryDatabase());
//        return new EshopServiceImpl(Database.DUMMY_DATABASE);
    }
    public static void main(String[] args) {
        // Create e-shop
        EshopService eshopService = createEshop();

        // Fill storage
        eshopService.addProductsToStorage(lenovoE500, hpBusinnesPlus, samsungMediaPlus);

        // Sort
        printProducts(eshopService.getProducts());
        printProducts("Products (sorted by name ASC)", eshopService.getProducts(new ProductNameComparator(SortOrder.ASCENDING)));
        printProducts("Products (sorted by price ASC)", eshopService.getProducts(new ProductPriceComparator(SortOrder.ASCENDING)));
        printProducts("Products (sorted by price DESC)", eshopService.getProducts(new ProductPriceComparator(SortOrder.DESCENDING)));
    }

}
