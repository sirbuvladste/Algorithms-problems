#include <stdio.h>
#include <stdlib.h>

int findMinNodes(int nrNodes, int** matrixLinks, int* nodeLinks) {
  int i, j;
  int maxLinks = 0;  // the maximum number of links a computer has

  // copy of the links of the eliminated node
  int* nodeLinksCopy;

  for (i = 0; i < nrNodes; i++) {
    if (maxLinks < nodeLinks[i]) {
      maxLinks = nodeLinks[i];
    }
  }

  int minNumbOfElim =
      __INT16_MAX__;    // the minimum number of elimination at a point
  int resultBT = 0;     // the minimum number of elimination at every step in BT
  int nodeCheck = 0;    // the node that has to be checked
  int removeNode = -1;  // the index of the node that has to be removed

  if (maxLinks > 0) {
    for (nodeCheck = 0; nodeCheck < nrNodes; nodeCheck++) {
      if (nodeLinks[nodeCheck] == maxLinks) {
        // save the links of the node that has been checked
        nodeLinksCopy = (int*)calloc(sizeof(int), nrNodes);
        for (i = 0; i < nrNodes; i++) {
          if (matrixLinks[nodeCheck][i] == 1) {
            // remove its links from the matrix
            // decrease the number of links of the adjuncted nodes
            nodeLinksCopy[i] = 1;
            matrixLinks[nodeCheck][i] = 0;
            matrixLinks[i][nodeCheck] = 0;
            nodeLinks[i] -= 1;
            nodeLinks[nodeCheck] -= 1;
          } else {
            nodeLinksCopy[i] = 0;
          }
        }

        resultBT = findMinNodes(nrNodes, matrixLinks, nodeLinks);
        if (resultBT < minNumbOfElim) {
          minNumbOfElim = resultBT;
          removeNode = nodeCheck;
        }

        for (i = 0; i < nrNodes; i++) {
          // restaurate the node's links and the number of links of the
          // adjuncted nodes
          if (nodeLinksCopy[i] == 1) {
            matrixLinks[nodeCheck][i] = nodeLinksCopy[i];
            matrixLinks[i][nodeCheck] = nodeLinksCopy[i];
            nodeLinks[i] += 1;
            nodeLinks[nodeCheck] += 1;
          }
        }
        // free the copy for the next node
        free(nodeLinksCopy);
      }
    }
    return 1 + minNumbOfElim;
  } else {
    return 0;
  }
}

/**
 * node = computer / monitor in the given problem
 */
int main() {
  int nrNodes = 0;
  int i = 0, j = 0;
  int node1 = 0, node2 = 0;
  int nrLinks = 0;
  printf("Input the number of nodes: ");
  scanf("%d", &nrNodes);
  printf("Input the number of links: ");
  scanf("%d", &nrLinks);

  // an dynamic matrix which represent the links
  // initialized with 0 on all positions
  // 0 = no link between nodes, 1 = link between nodes
  int** matrixLinks = (int**)calloc(nrNodes, sizeof(int*));
  for (i = 0; i < nrNodes; i++) {
    matrixLinks[i] = (int*)calloc(nrNodes, sizeof(int));

    for (j = 0; j < nrNodes; j++) {
      matrixLinks[i][j] = 0;
    }
  }

  // frequency vector for the number of links every node has
  int* nodeLinks = (int*)calloc(sizeof(int), nrNodes);

  // input: number of nodes, number of links and then the links of form:
  // node1 to node2
  printf("Input the links (format: node1 node2):\n");
  for (i = 0; i < nrLinks; i++) {
    scanf("%d %d", &node1, &node2);
    if (node1 == node2) {
      printf(
          "The link can not start and end at the same computer!\nTry again!\n");
      --i;
      continue;
    }
    matrixLinks[--node1][--node2] = 1;  // set the links
    matrixLinks[node2][node1] = 1;
    nodeLinks[node1]++;
    nodeLinks[node2]++;
  }

  int result = 0;
  result = findMinNodes(nrNodes, matrixLinks, nodeLinks);
  printf("The minimum number of computers that have to checked: %d\n", result);
  return 0;
}