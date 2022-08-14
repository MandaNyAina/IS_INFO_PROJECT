from scrapy import Spider, Request

from ..items import ScrapingServicesItem


class SupermarcheSpider(Spider):
    name = 'supermarche'
    allowed_domains = ['supermarche.mg']
    start_urls = 'https://supermarche.mg/rayon/viande/boeuf/'

    def start_requests(self):
        yield Request(url=self.start_urls, callback= self.parse)

    def parse(self, response):
        products_blocks = response.css(".woocommerce .has-wc-sidebar div.products.shop-5column.fullwidthshop div.product")
        for product_block in products_blocks:
            product_price = product_block.css("bdi::text").extract_first()
            if product_price:
                item = ScrapingServicesItem()

                item['product_name'] = product_block.css("h2.woocommerce-loop-product__title::text").extract_first()
                item['product_price'] = product_price
                
                yield item
