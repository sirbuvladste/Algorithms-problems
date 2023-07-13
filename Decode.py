import itertools

def checkSeq(seq, key, firstKey, seqStart):
  i = 0
  # check until the end of the seq or until all key are checked
  while len(seq) > 0 and i < len(key)-1:
    # go through all key
    for i in range(0,len(key)):
      ''' start the decoding with a different key than the one
          that started the sequence '''
      if ((seqStart != 0) or (seqStart == 0 and i != firstKey)):
        ''' check if the curent key is at the beginning of the sequence
            if not go to the next key (or end the loop) '''
        if seq.find(key[i]) == 0:
          ''' using the current key and backtracking continue to decode
              the rest of the sequence, if using this key its not possible
              to decode than go to the next key '''
          if (len(key[i])<=len(seq) and
          checkSeq(seq[len(key[i]):len(seq)], key, firstKey, 1) == 1):
            return 1
  # if the full sequence has been decoded than the task has been fulfilled
  if len(seq) == 0:
    return 1
  return 0


def searchBT(seq, key,  vectFreq, firstKey):
  for posInKey in range(len(key)):
    # save the first key for checking the sequence
    if len(seq) == 0:
      firstKey = posInKey

    ''' put the key in the sequence, but if it appears more than
        twice then we skip that sequence '''
    if vectFreq[posInKey] < 2:
      seq += key[posInKey]
      vectFreq[posInKey] += 1
    else: continue

    # check the seq if can be decoded any other way
    if checkSeq(seq, key, firstKey, 0) == 1:
      # to print the first sequence that can be decoded: print(seq)
      return 1
    else:
      ''' if current sequence did not decode any other way,
          check if there can be formed another sequence from 
          the current one that can be decoded '''
      if searchBT(seq, key, vectFreq, firstKey) == 1:
        return 1
    # reset the sequence with one key back
    seq = seq[0:(len(seq)-len(key[posInKey]))]
    vectFreq[posInKey] = 1
  return 0



inp = input('Input the keys in order to search a sequence: ')
key = tuple(str(val) for val in inp.split())
vectFreq = [0] * len(key)
seq = ""

result = searchBT(seq, key,  vectFreq, -1)
if result == 1:
  print("YES - Using the keys it can be formed a sequence " + 
        "which can be decoded in several ways.")
else:
  print("NO - Using the keys given it can not be formed a sequence " + 
        "which can be decoded in several ways.")



