# VADER-Sentiment-Analysis-in-C
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
  2. A lexicon file `vader_lexicon.txt` containing words with sentiment scores and sentiment distributions from human ratings.
 
- Output: The sentiment scores for the input text, including:
  1. Positive score (pos)
  2. Negative score (neg)
  3. Neutral score (neu)
  4. Compound score (compound) - representing the overall sentiment strength, normalized to range from -1 to 1. 

## Lexicon File (vader_lexicon.txt)
The file `vader_lexicon.txt` contains words with associated sentiment values and distributions. The following table shows the format of a few lines in this file:

`Table 1: The contents of given lexicon file vaderlexicon.txt from vaderSentiment`
`Word Sentiment Value 1 Sentiment Value 2 Array of Distribution`
`smart 1.7 0.78102 [2, 2, 1, 2, 1, 3, 2, 0, 2, 2]`
`funny 1.9 0.53852 [3, 2, 2, 1, 2, 2, 1, 2, 2, 2]`
`handsome 2.2 0.74833 [2, 2, 2, 2, 2, 3, 4, 1, 2, 2]`
`guilty -1.8 0.6 [-1, -2, -2, -3, -2, -2, -1, -2, -2, -1]`

Each line contains:
- A word (word) as a string. 
- Two floating-point values (Sentiment value 1 and Sentiment Value 2), representing the average sentiment score and the standard deviation, respectively.
- An array of integers (Array of Distribution) representing human sentiment ratings distribution for each word. These ratings show the range of sentiment perceptions across different people. 
