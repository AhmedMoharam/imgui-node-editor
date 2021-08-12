import yfinance as yf
import pandas as pd
import numpy as np


def histDataDataframe(ticker, period="2y", interval='1d'):
    sym = yf.Ticker(ticker)
    sym_data = sym.history(period=period, interval=interval, actions=False)
    return sym_data

class TradingClass:
    def RSI(self, ticker, n=20):
        """function to calculate RSI"""
        n = int(n)
        DF = histDataDataframe(ticker)

        df = DF.copy()
        df['delta'] = df['Close'] - df['Close'].shift(1)
        df['gain'] = np.where(df['delta'] >= 0, df['delta'], 0)
        df['loss'] = np.where(df['delta'] < 0, abs(df['delta']), 0)
        avg_gain = []
        avg_loss = []
        gain = df['gain'].tolist()
        loss = df['loss'].tolist()
        for i in range(len(df)):
            if i < n:
                avg_gain.append(np.NaN)
                avg_loss.append(np.NaN)
            elif i == n:
                avg_gain.append(df['gain'].rolling(n).mean()[n])
                avg_loss.append(df['loss'].rolling(n).mean()[n])
            elif i > n:
                avg_gain.append(((n - 1) * avg_gain[i - 1] + gain[i]) / n)
                avg_loss.append(((n - 1) * avg_loss[i - 1] + loss[i]) / n)
        df['avg_gain'] = np.array(avg_gain)
        df['avg_loss'] = np.array(avg_loss)
        df['RS'] = df['avg_gain'] / df['avg_loss']
        df['RSI'] = 100 - (100 / (1 + df['RS']))
        #print(df['RSI'][::-1][0])
        return float(df['RSI'][::-1][0])

    def OBV(self, stock, start='2020-01-01', end='2021-01-01', days=14):
        df = yf.download(stock, start, end)
        obv = []
        obv.append(0)
        for i in range(1, len(df["Close"])):
            if df["Close"][i] > df["Close"][i - 1]:
                obv.append(obv[-1] + df["Volume"][i])
            elif df["Close"][i] < df["Close"][i - 1]:
                obv.append(obv[-1] - df["Volume"][i])
            else:
                obv.append(obv[-1])

        #print(obv[::-1][0])

        return float(obv[::-1][0])

    def MACD(self, stock, start='2020-01-01', end='2021-01-01', PRICE_NAME="Close", period1=26, period2=12, period3=9):
        df = yf.download(stock, start, end)
        EMA_1 = df[PRICE_NAME].ewm(span=period1, adjust=False).mean()
        EMA_2 = df[PRICE_NAME].ewm(span=period2, adjust=False).mean()
        MACD_line = EMA_2 - EMA_1
        MACD_Signal_line = MACD_line.ewm(span=period3, adjust=False).mean()
        MACD_Histogram = MACD_line - MACD_Signal_line
        #print(MACD_line, MACD_Signal_line, MACD_Histogram)
		#print(MACD_line[::-1][0])
        return float(MACD_line[::-1][0])

    def IchimokuCloud(self, Stock, startDate='2019-01-01', endDate='2021-01-01'):
        # df = yf.download('AAPL', '2019-01-01', '2021-01-01')
        #print ("start date: {}, end date: {}".format(startDate, endDate))
        df = yf.download(Stock, startDate, endDate)

        # Define length of Tenkan Sen or Conversion Line
        cl_period = 20

        # Define length of Kijun Sen or Base Line
        bl_period = 60

        # Define length of Senkou Sen B or Leading Span B
        lead_span_b_period = 120

        # Define length of Chikou Span or Lagging Span
        lag_span_period = 30

        # Calculate conversion line
        high_20 = df['High'].rolling(cl_period).max()
        low_20 = df['Low'].rolling(cl_period).min()
        df['conversion_line'] = (high_20 + low_20) / 2

        # Calculate based line
        high_60 = df['High'].rolling(bl_period).max()
        low_60 = df['Low'].rolling(bl_period).min()
        df['base_line'] = (high_60 + low_60) / 2

        # Calculate leading span A
        df['lead_span_A'] = ((df.conversion_line + df.base_line) / 2).shift(lag_span_period)

        # Calculate leading span B
        high_120 = df['High'].rolling(120).max()
        low_120 = df['High'].rolling(120).min()
        df['lead_span_B'] = ((high_120 + low_120) / 2).shift(lead_span_b_period)

        # Calculate lagging span
        df['lagging_span'] = df['Close'].shift(-lag_span_period)

        # Drop NA values from Dataframe
        df.dropna(inplace=True)
		#print(df[::-1]["base_line"][0])
        return float(df[::-1]["base_line"][0])

    def WILLIAMS(self, stock, start='2020-01-01', end='2021-01-01', days=14):
        df = yf.download(stock, start, end)
        highh = df["High"].rolling(days).max()
        lowl = df["Low"].rolling(days).min()
        close = df["Close"]
        wr = -100 * ((highh - close) / (highh - lowl))

        #print(wr[::-1][0])

        return float(wr[::-1][0])