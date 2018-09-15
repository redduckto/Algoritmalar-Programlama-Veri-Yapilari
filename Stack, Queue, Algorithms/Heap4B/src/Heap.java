
public class Heap {

    private HeapNode[] heapArray;
    private int SIZE;               //array size
    private int nElems;             //number of heap nodes


    public Heap(int SIZE) {

        this.SIZE=SIZE;
        nElems=0;
        heapArray=new HeapNode[SIZE];
    }

    public boolean isEmpty(){

        if (nElems==0) {              //check if there are elements in heaparray
            return true;
        }
        return false;
    }

    public boolean insert(int key){

        if(nElems==SIZE)
            return false;
        else
            heapArray[nElems]=new HeapNode(key);
            sortUp(nElems);
            nElems++;
            return true;

    }

    public HeapNode remove(){



        HeapNode root=heapArray[0];
            heapArray[0]=heapArray[--nElems];
            sortDown(0);
            return root;


    }

    public void sortUp(int index){

        int parent=(index-1)/2;
        HeapNode end=heapArray[nElems];
        while(index>0&&heapArray[parent].getKey()<end.getKey()) {
            heapArray[index] = heapArray[parent];
            index = parent;
            parent = (parent - 1) / 2;
        }
        heapArray[index]=end;

    }
    public void sortDown(int index){

        int biggerChild;
        HeapNode top=heapArray[index];
            while(index<nElems/2){

                int leftchild=2*index+1;
                int rightchild=2*index+2;
                if(rightchild<nElems&&heapArray[leftchild].getKey()<heapArray[rightchild].getKey())
                    biggerChild=rightchild;
                else
                    biggerChild=leftchild;

                if(top.getKey()>=heapArray[biggerChild].getKey())
                    break;
                heapArray[index]=heapArray[biggerChild];
                index=biggerChild;

            }
        heapArray[index]=top;

    }
    public boolean change(int index,int newvalue){


        if(index<0||index>=nElems)
            return false;
        int oldvalue=heapArray[index].getKey();
        heapArray[index].setKey(newvalue);
        if(oldvalue<newvalue)
            sortUp(index);
        else
            sortDown(index);
        return true;

    }
    public void displayHeap() {
        System.out.print("heapArray:");
        for (int m = 0; m < nElems; m++)
            if (heapArray[m] != null)
                System.out.print(heapArray[m].getKey() + " ");
            else
                System.out.print("--");
        System.out.println();

        int nBlanks = 32;
        int itemsPerRow = 1;
        int column = 0;
        int j = 0; // current item
        String dots = "...............................";
        System.out.println(dots+dots); // dotted top line
        while(nElems > 0) // for each heap item
        {
            if(column == 0) // first item in row?
                for(int k=0; k<nBlanks; k++) // preceding blanks
                    System.out.print(" ");
// display item
            System.out.print(heapArray[j].getKey());

            if(++j ==nElems) // done?
                break;
            if(++column==itemsPerRow) // end of row?
            {
                nBlanks /= 2; // half the blanks
                itemsPerRow *= 2; // twice the items
                column = 0; // start over on
                System.out.println(); // new row
            }
            else // next item on row
                for(int k=0; k<nBlanks*2-2; k++)
                    System.out.print(" "); // interim blanks
        } // end for
        System.out.println("\n"+dots+dots); // dotted bottom line
    } // end displayHeap()

    }

