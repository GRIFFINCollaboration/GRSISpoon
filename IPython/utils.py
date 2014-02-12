#get all the ROOT goodness
import ROOT
from ROOT import gROOT, TCanvas, TF1, TFile, TTree, gRandom, TH1F
import numpy


def ROOTplot(plotVar):
    #from ROOT import TFile, TTree
    #import rootnotes

    canvas = rootnotes.canvas("treeData", (600,400))

    testfile = TFile("fragment27422_000.root")
    testtree = testfile.Get("FragmentTree")

    buff = numpy.zeros(1, dtype=float)

    testtree.Branch(plotVar, buff)

    testtree.Draw(plotVar)

    return canvas



def listtree():

    testfile = TFile("fragment27422_000.root")
    testtree = testfile.Get("FragmentTree")

    entries = testtree.GetListOfLeaves().GetEntries()

    leaves = ""

    for x in range (0, entries):
        leaves += str(testtree.GetListOfLeaves()[x]).split('"')[1] + "&"; #& delimited for JS to split into an array

    return leaves;
