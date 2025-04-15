package model.solvers;

import controller.TileUpdate;
import controller.ViewUpdatePacket;
import model.*;
import utilities.Constants;

import java.util.*;


public class FloodFillSearchSolver extends Solver{

    private int[][] intGrid = new int[16][16];

    private VirtualCell currentVirtualCell = startPoint;

    private RealityCell currentRealityCell = this.getRealityGrid().getRealityCell(startPoint.getxPos(), startPoint.getyPos());
    public FloodFillSearchSolver(RealityGrid grid) {
        super(grid);
    }


    public FloodFillSearchSolver(RealityGrid grid, RealityCell startPoint, ArrayList<RealityCell> endPoints){
        super(grid, startPoint, endPoints);
    }
    public VirtualCell getCurrentVirtualCell() {
        return currentVirtualCell;
    }

    public RealityCell getCurrentRealityCell() {return currentRealityCell;}

    public void fill(ArrayList<VirtualCell> endpoints){
        intGrid = new int[16][16];
        for (int y = 0; y < 16; ++y) {
            for (int x = 0; x < 16; ++x) {
                intGrid[y][x] = 694;
            }
        }

        Queue<VirtualCell> cellQueue = new LinkedList<>();
        for (VirtualCell endPoints : endpoints){
            cellQueue.add(endPoints);
            intGrid[endPoints.getyPos()][endPoints.getxPos()] = 0;
        }

        while (!cellQueue.isEmpty()) {
            VirtualCell currentCell = cellQueue.poll();
            int newValue = intGrid[currentCell.getyPos()][currentCell.getxPos()] + 1;

            for (VirtualCell neighborCell : getVirtualGrid().getAdjacentVirtualCells(currentCell)) {
                try {
                    if (!getVirtualGrid().isTherePathBetweenVirtualCells(currentCell, neighborCell)) continue;
                } catch(Exception ignored) {}

                final int neighborX = neighborCell.getxPos();
                final int neighborY = neighborCell.getyPos();

                if (newValue < intGrid[neighborY][neighborX]) {
                    intGrid[neighborY][neighborX] = newValue;
                    cellQueue.add(neighborCell);
                }
            }
        }
    }

    @Override
    public ViewUpdatePacket makeViewUpdatePacket() {
        ViewUpdatePacket updatePacket = new ViewUpdatePacket(new ArrayList<>(300));


        for (int x = Constants.minCellIndex; x <= Constants.maxCellIndex; x++) {
            for (int y = Constants.minCellIndex; y <= Constants.maxCellIndex; y++) {

                Cell cell = this.getRealityGrid().getRealityCell(x, y);


                TileUpdate tileUpdate = Cell.makeTileUpdateFromCell(cell, false, false);
                updatePacket.addTileUpdate(tileUpdate);
            }
        }

        // Add the current cell at the end, will override its earlier addition
        if (this.getCurrentRealityCell() != null) {
            TileUpdate tileUpdate = Cell.makeTileUpdateFromCell(this.getCurrentRealityCell(), true, false);
            updatePacket.addTileUpdate(tileUpdate);
        }

        return updatePacket;
    }

    public int[][] getIntGrid(){
        return intGrid;
    }

    public void iterate(){
        if(this.isDone()){

        }
        else if(this.atDestination(currentVirtualCell)){
            this.setDone(true);
        }
        else{
            currentRealityCell.setTraversed(true);
            this.updateVirtualGrid(currentRealityCell);
            this.fill(this.endPoints);
            int currentValue = intGrid[currentVirtualCell.getyPos()][currentVirtualCell.getxPos()];
            int currentXPos = currentVirtualCell.getxPos();
            int currentYPos = currentVirtualCell.getyPos();
            boolean choseNext = false;
            if(currentYPos<15){
                if(intGrid[currentYPos+1][currentXPos] == currentValue-1) {
                    try {
                        if (this.getVirtualGrid().isTherePathBetweenVirtualCells(this.getVirtualGrid().getVirtualCell(currentXPos, currentYPos + 1), this.currentVirtualCell)) {
                            currentVirtualCell = this.getVirtualGrid().getVirtualCell(currentXPos, currentYPos + 1);
                            choseNext = true;
                        }
                    }
                    catch (Exception e){

                    }
                }
            }
            if(currentYPos>0 && !choseNext){
                if(intGrid[currentYPos-1][currentXPos] == currentValue-1) {
                    try {
                        if (this.getVirtualGrid().isTherePathBetweenVirtualCells(this.getVirtualGrid().getVirtualCell(currentXPos, currentYPos - 1), this.currentVirtualCell)) {
                            currentVirtualCell = this.getVirtualGrid().getVirtualCell(currentXPos, currentYPos - 1);
                            choseNext = true;
                        }
                    }
                    catch (Exception e){

                    }
                }
            }
            if(currentXPos<15 && !choseNext){
                if(intGrid[currentYPos][currentXPos+1] == currentValue-1) {
                    try {
                        if (this.getVirtualGrid().isTherePathBetweenVirtualCells(this.getVirtualGrid().getVirtualCell(currentXPos + 1, currentYPos), this.currentVirtualCell)) {
                            currentVirtualCell = this.getVirtualGrid().getVirtualCell(currentXPos + 1, currentYPos);
                            choseNext = true;
                        }
                    }
                    catch (Exception e){

                    }
                }
            }
            if(currentXPos>0 && !choseNext){
                if(intGrid[currentYPos][currentXPos-1] == currentValue-1) {
                    try {
                        if (this.getVirtualGrid().isTherePathBetweenVirtualCells(this.getVirtualGrid().getVirtualCell(currentXPos - 1, currentYPos), this.currentVirtualCell)) {
                            currentVirtualCell = this.getVirtualGrid().getVirtualCell(currentXPos - 1, currentYPos);
                            choseNext = true;
                        }
                    }
                    catch (Exception e){

                    }
                }
            }
            currentRealityCell = this.getRealityGrid().getRealityCell(currentVirtualCell.getxPos(), currentVirtualCell.getyPos());
        }

    }

    public void finish(){
        this.setEndpointsAsTargetDestination();
        this.setDone(false);
        while (!this.isDone()) {
            this.iterate();
        }
    }

    public void iterateReversed(){
        if(this.isDone()){

        }
        else if(this.atDestination(currentVirtualCell)){
            this.setDone(true);
        }
        else{
            currentRealityCell.setTraversed(true);
            this.updateVirtualGrid(currentRealityCell);
            ArrayList<VirtualCell> endpoint = new ArrayList<>();
            endpoint.add(startPoint);
            this.fill(endpoint);
            int currentValue = intGrid[currentVirtualCell.getyPos()][currentVirtualCell.getxPos()];
            int currentXPos = currentVirtualCell.getxPos();
            int currentYPos = currentVirtualCell.getyPos();
            boolean choseNext = false;
            if(currentYPos>0){
                if(intGrid[currentYPos-1][currentXPos] == currentValue-1) {
                    try {
                        if (this.getVirtualGrid().isTherePathBetweenVirtualCells(this.getVirtualGrid().getVirtualCell(currentXPos, currentYPos - 1), this.currentVirtualCell)) {
                            currentVirtualCell = this.getVirtualGrid().getVirtualCell(currentXPos, currentYPos - 1);
                            choseNext = true;
                        }
                    }
                    catch (Exception e){

                    }
                }
            }
            if(currentXPos>0 && !choseNext){
                if(intGrid[currentYPos][currentXPos-1] == currentValue-1) {
                    try {
                        if (this.getVirtualGrid().isTherePathBetweenVirtualCells(this.getVirtualGrid().getVirtualCell(currentXPos - 1, currentYPos), this.currentVirtualCell)) {
                            currentVirtualCell = this.getVirtualGrid().getVirtualCell(currentXPos - 1, currentYPos);
                            choseNext = true;
                        }
                    }
                    catch (Exception e){

                    }
                }
            }
            if(currentYPos<15 && !choseNext){
                if(intGrid[currentYPos+1][currentXPos] == currentValue-1) {
                    try {
                        if (this.getVirtualGrid().isTherePathBetweenVirtualCells(this.getVirtualGrid().getVirtualCell(currentXPos, currentYPos + 1), this.currentVirtualCell)) {
                            currentVirtualCell = this.getVirtualGrid().getVirtualCell(currentXPos, currentYPos + 1);
                            choseNext = true;
                        }
                    }
                    catch (Exception e){

                    }
                }
            }
            if(currentXPos<15 && !choseNext){
                if(intGrid[currentYPos][currentXPos+1] == currentValue-1) {
                    try {
                        if (this.getVirtualGrid().isTherePathBetweenVirtualCells(this.getVirtualGrid().getVirtualCell(currentXPos + 1, currentYPos), this.currentVirtualCell)) {
                            currentVirtualCell = this.getVirtualGrid().getVirtualCell(currentXPos + 1, currentYPos);
                            choseNext = true;
                        }
                    }
                    catch (Exception e){

                    }
                }
            }
//            if(!choseNext){
//                ArrayList<VirtualCell> reachableAdjacentCells = this.getVirtualGrid().getReachableAdjacentVirtualCells(this.currentVirtualCell);
//                if(reachableAdjacentCells.size()==1){
//                    this.currentVirtualCell.addLeftBorder();
//                    this.currentVirtualCell.addTopBorder();
//                    this.currentVirtualCell.addRightBorder();
//                    this.currentVirtualCell.addBottomBorder();
//                    this.currentVirtualCell = reachableAdjacentCells.get(0);
//                }
//                else{
//                    this.currentVirtualCell = reachableAdjacentCells.get((int)(Math.random()*reachableAdjacentCells.size()));
//                }
//            }
            currentRealityCell = this.getRealityGrid().getRealityCell(currentVirtualCell.getxPos(), currentVirtualCell.getyPos());
        }
    }

    @Override
    public void backToStart(){
        this.setStartAsTargetDestination();
        this.setDone(false);
        System.out.println("new rerun");
        int x = 0;
        while(!this.isDone()) {
            if (x < 60){
                System.out.println(this.currentVirtualCell.getxPos() + ", " + this.currentVirtualCell.getyPos());
                x++;
                System.out.println("this is the int grid at this point");
                printIntGrid();
            }
            this.iterateReversed();
        }

    }

    public void printIntGrid(){
        for(int y = 0; y < Constants.mazeLength; y++){
            System.out.print("[");
            for(int x = 0; x < Constants.mazeLength; x++){
                System.out.printf("%4d", intGrid[y][x]);
            }
            System.out.println("]");
        }
    }
}
