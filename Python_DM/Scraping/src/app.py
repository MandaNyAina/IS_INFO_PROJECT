import pandas as pd
from matplotlib.pyplot import pie, show, text, subplot, plot, xticks

class BeefAnalysis:

    def show(self, datasets):
        df = pd.read_csv(datasets)
        count_by_key = df.groupby(["key"])["key"].count()

        subplot_index = int(f"{len(count_by_key) + 1}11")

        subplot(subplot_index)
        self.show_pie(count_by_key)

        for key in count_by_key.index:
            products_price_by_seller = [float(value.replace(" ", "").replace(u'\xa0', u' ')) for value in df.loc[df['key'] == key, 'product_price'].values]
            subplot_index += 1
            subplot(subplot_index)
            self.show_bar(key, products_price_by_seller)

        show()

    def show_pie(self, count_by_key):
        text(-3.1, 1.1, "Qui vend plus de viande ?")
        pie(count_by_key, labels=count_by_key.index)

    def show_bar(self, key, products_price_by_seller):
        uniq_products_price = list(set(products_price_by_seller))
        plot(uniq_products_price)
        text(0, max(products_price_by_seller) - 10000, f"Variation de prix chez {key} avec un montant \n - min : {min(products_price_by_seller)} Ariary\n - max : {max(products_price_by_seller)} Ariary")
        xticks(color='w')