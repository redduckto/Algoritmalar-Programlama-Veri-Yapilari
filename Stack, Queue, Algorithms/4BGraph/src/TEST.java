
class TEST
{
    public static void main(String[] args)
    {
        Graph theGraph = new Graph();
        theGraph.addVertex('K');
        theGraph.addVertex('L');
        theGraph.addVertex('N');
        theGraph.addVertex('P');
        theGraph.addVertex('R');

        theGraph.addEdge(0, 1);
        theGraph.addEdge(0, 2);
        theGraph.addEdge(0, 3);
        theGraph.addEdge(0, 4);
        theGraph.addEdge(1, 2);
        theGraph.addEdge(1, 3);
        theGraph.addEdge(1, 4);
        theGraph.addEdge(2, 3);
        theGraph.addEdge(2, 4);
        theGraph.addEdge(3, 4);

        Graph theGraph1 = new Graph();
        theGraph1.addVertex('C');
        theGraph1.addVertex('E');
        theGraph1.addVertex('I');
        theGraph1.addVertex('S');
        theGraph1.addVertex('W');
        theGraph1.addEdge(0, 1);
        theGraph1.addEdge(1, 2);
        theGraph1.addEdge(0, 3);
        theGraph1.addEdge(3, 4);



        System.out.print("Minimum spanning tree:");
        theGraph.mst();
        System.out.println();
        System.out.println();
        System.out.println();
        System.out.print("Breadth First Path Visits:");
        theGraph1.bfs();
        System.out.println();
    }
}
