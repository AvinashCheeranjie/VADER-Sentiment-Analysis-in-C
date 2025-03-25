from vaderSentiment import SentimentIntensityAnalyzer

# --- example sentences -------
sentences = ["VADER is smart, handsome, and funny.",  # neg: 0.0, neu: 0.254, pos: 0.746, compound: 0.8316
             "VADER is smart, handsome, and funny!",  # compound: 0.8439
             "VADER is very smart, handsome, and funny.", # compound: 0.8545
             "VADER is VERY SMART, handsome, and FUNNY.",  # emphasis for ALLCAPS handled
             "VADER is VERY SMART, handsome, and FUNNY!!!", # combination of signals - VADER appropriately adjusts intensity
             "VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!", # booster words & punctuation make this close to ceiling for score
             "VADER is not smart, not handsome, nor funny.",  # negation sentence example
             "At least it isn't a horrible book.",  # negated negative sentence with contraction
             "The plot was good, but the characters are uncompelling and the dialog is not great.", # mixed negation sentence
             "Make sure you :) or :D today!",  # emoticons handled
             "Not bad at all"  # Capitalized negation
             ]

analyzer = SentimentIntensityAnalyzer()
for sentence in sentences:
    vs = analyzer.polarity_scores(sentence)
    print("{:-<65} {}".format(sentence, str(vs)))

"""
VADER is smart, handsome, and funny.---------------------------- {'neg': 0.0, 'neu': 0.254, 'pos': 0.746, 'compound': 0.8316}
VADER is smart, handsome, and funny!---------------------------- {'neg': 0.0, 'neu': 0.248, 'pos': 0.752, 'compound': 0.8439}
VADER is very smart, handsome, and funny.----------------------- {'neg': 0.0, 'neu': 0.299, 'pos': 0.701, 'compound': 0.8545}
VADER is VERY SMART, handsome, and FUNNY.----------------------- {'neg': 0.0, 'neu': 0.246, 'pos': 0.754, 'compound': 0.9227}
VADER is VERY SMART, handsome, and FUNNY!!!--------------------- {'neg': 0.0, 'neu': 0.233, 'pos': 0.767, 'compound': 0.9342}
VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!-------- {'neg': 0.0, 'neu': 0.294, 'pos': 0.706, 'compound': 0.9469}
VADER is not smart, not handsome, nor funny.------------------------ {'neg': 0.646, 'neu': 0.354, 'pos': 0.0, 'compound': -0.7424}
At least it isn't a horrible book.------------------------------ {'neg': 0.0, 'neu': 0.678, 'pos': 0.322, 'compound': 0.431}
The plot was good, but the characters are uncompelling and the dialog is not great. {'neg': 0.327, 'neu': 0.579, 'pos': 0.094, 'compound': -0.7042}
Make sure you :) or :D today!----------------------------------- {'neg': 0.0, 'neu': 0.294, 'pos': 0.706, 'compound': 0.8633}
Not bad at all-------------------------------------------------- {'neg': 0.0, 'neu': 0.513, 'pos': 0.487, 'compound': 0.431}
"""   