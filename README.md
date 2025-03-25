# Vader-Sentiment-Analysis-in-C
Sentiment analysis is a Natural Language Processing (NLP) technique used to determine and
analyze emotions, opinions, and subjective information within text data. It’s widely employed to
assess sentiments in social media posts, customer reviews, and other written feedback, categorizing
text as positive, negative, neutral, or more granular emotional states. If you need more information,
read: [AWS - What is Sentiment Analysis.](https://aws.amazon.com/what-is/sentiment-analysis/)

VADER (Valence Aware Dictionary for Sentiment Reasoning) is a rule-based sentiment analysis
tool specifically tuned for social media. It uses a predefined lexicon of words associated with specific
sentiment intensities, making it effective at handling context-heavy content such as slang, emojis,
and varying intensities of emotions. VADER outputs sentiment scores for positive, negative, and
neutral tones, as well as a compound score that represents the overall sentiment. For more details,
see:[ VADER Sentiment Analysis.](https://blog.quantinsti.com/vader-sentiment/#:~:text=that%20hot.%E2%80%9D.-,Compound%20VADER%20scores%20for%20analyzing%20sentiment,1%20(most%20extreme%20positive))

## Problem Statement
In this assignment, I implemented a simplified version of the VADER sentiment analysis tool in C. The VADER implementation involves reading a lexicon file, identifying sentiment-bearing words within a sentence, and applying specific rules to calculate sentiment scores. Inputs
and Outputs are as follows:
- Input:
  1. A sentence string (e.g., "VADER is very smart, handsome, and funny.").
  2. A lexicon file (vaderlexicon.txt) containing words with sentiment scores and senti-
ment distributions from human ratings.
