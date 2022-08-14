from itertools import product
from scrapy import Spider, Request

from ..items import ScrapingServicesItem


class TsenabeSpider(Spider):
    name = 'tsenabe'
    allowed_domains = ['tsenabe.mg']
    start_urls = 'https://tsenabe.mg/categorie-produit/viande/zebu/'

    def start_requests(self):
        yield Request(url=self.start_urls, callback=self.parse)

    def parse(self, response):
        products_block = response.css(".woocommerce ul.products li.product, .woocommerce-page ul.products li.product")
        for product_block in products_block:
            item = ScrapingServicesItem()

            item['product_name'] = product_block.css("h2.woocommerce-loop-product__title::text").extract_first()
            item['product_price'] = product_block.css("bdi::text").extract_first()
            
            yield item
