import argparse
from ROOT import *

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--input", required=True, type=str,
                    help="Path to the .root file created by the output of EntanglementAnalysis of j-pet-framework-examples")
# parser.add_argument("-o", "--output", required=True,
# help="Path to the directory in which you want to store .png files")
parser.add_argument("-w", "--width", required=False, type=int, default=2,
                    help="Line width on 1D histograms")

args = vars(parser.parse_args())

LineWidth = args["width"]


def main():
    canvas = TCanvas("Canvas_1", "Canvas_1", 533, 76, 1383, 852)

    gStyle.SetPalette(kRainBow)

    input_file = TFile(args["input"])

    Z_pos = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/Z_pos_all")
    Z_pos.GetYaxis().SetTitleOffset(1.2)
    Z_pos.SetLineWidth(LineWidth)
    Z_pos.Draw()
    canvas.SaveAs("Zpos.png")

    TimeDiffTOFcorrecter = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_TimeDiff_TOFcorrected")
    TimeDiffTOFcorrecter.GetYaxis().SetTitleOffset(1.2)
    TimeDiffTOFcorrecter.Rebin(2)
    TimeDiffTOFcorrecter.SetLineWidth(LineWidth)
    TimeDiffTOFcorrecter.Draw()

    TimeDiff = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_TimeDiff")
    TimeDiff.GetYaxis().SetTitleOffset(1.2)
    TimeDiff.Rebin(2)
    TimeDiff.SetLineColor(2)
    TimeDiff.SetLineWidth(LineWidth)
    TimeDiff.Draw("SAME")

    canvas.SaveAs("TimeDiff.png")

    TimeDiffTOFcorrecter.SetAxisRange(0, 4, "X")
    TimeDiff.SetAxisRange(0, 4, "X")

    canvas.Update()
    canvas.SaveAs("TimeDiffZoomed.png")

    TOT = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/AllHitTOT")
    TOT.GetYaxis().SetTitleOffset(1.2)
    TOT.SetLineWidth(LineWidth)
    TOT.SetAxisRange(0, 80, "X")
    TOT.Draw()
    cut1 = TLine(1, 0, 1, 1.1 * TOT.GetMaximum())
    cut2 = TLine(25, 0, 25, 1.1 * TOT.GetMaximum())
    cut1.SetLineWidth(LineWidth)
    cut2.SetLineWidth(LineWidth)
    cut1.Draw("SAME")
    cut2.Draw("SAME")
    canvas.SaveAs("TOT.png")

    BTB_Z_pos = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_z_pos")
    BTB_Z_pos.GetYaxis().SetTitleOffset(1.2)
    BTB_Z_pos.SetLineWidth(LineWidth)
    BTB_Z_pos.SetAxisRange(-10, 10, "X")
    BTB_Z_pos.Draw()

    canvas.SaveAs("AnniZpos.png")

    BTBangle3D = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_ThetaDiff3DAcos")
    BTBangle3D.GetYaxis().SetTitleOffset(1.2)
    BTBangle3D.SetLineWidth(LineWidth)
    BTBangle3D.Draw()

    canvas.SaveAs("BTBangle3D.png")

    BTBangle3D_timeCut = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_ThetaDiff3DAcos_timeDiffCut")
    BTBangle3D_timeCut.GetYaxis().SetTitleOffset(1.2)
    BTBangle3D_timeCut.SetLineWidth(LineWidth)
    BTBangle3D_timeCut.Draw()

    canvas.SaveAs("BTBangle3D_timeCut.png")

    BTBangle3D_zCut = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_ThetaDiff3DAcos_Zcut")
    BTBangle3D_zCut.GetYaxis().SetTitleOffset(1.2)
    BTBangle3D_zCut.SetLineWidth(LineWidth)
    BTBangle3D_zCut.Draw()

    canvas.SaveAs("BTBangle3D_zCut.png")

    BTBangle2D = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_ThetaDiff2DAcos")
    BTBangle2D.GetYaxis().SetTitleOffset(1.2)
    BTBangle2D.SetLineWidth(LineWidth)
    BTBangle2D.Draw()

    canvas.SaveAs("BTBangle2D.png")

    PhiAngle = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/PhiAngle")
    PhiAngle.GetYaxis().SetTitleOffset(1.2)
    PhiAngle.SetLineWidth(LineWidth)
    PhiAngle.Rebin(5)
    PhiAngle.SetAxisRange(0, 1.1 * PhiAngle.GetMaximum(), "Y")
    PhiAngle.Draw()

    canvas.SaveAs("PhiAngle.png")

    PhiAngleCenter = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/PhiAngleR10")
    PhiAngleCenter.GetYaxis().SetTitleOffset(1.2)
    PhiAngleCenter.SetLineWidth(LineWidth)
    PhiAngleCenter.Rebin(10)
    PhiAngleCenter.SetAxisRange(0, 1.1 * PhiAngleCenter.GetMaximum(), "Y")
    PhiAngleCenter.Draw()

    canvas.SaveAs("PhiAngleR10.png")

    PhiAngleCenter = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/PhiAngleR15")
    PhiAngleCenter.GetYaxis().SetTitleOffset(1.2)
    PhiAngleCenter.SetLineWidth(LineWidth)
    PhiAngleCenter.Rebin(10)
    PhiAngleCenter.SetAxisRange(0, 1.1 * PhiAngleCenter.GetMaximum(), "Y")
    PhiAngleCenter.Draw()

    canvas.SaveAs("PhiAngleR15.png")

    PhiAngleCenter = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/PhiAngleR20")
    PhiAngleCenter.GetYaxis().SetTitleOffset(1.2)
    PhiAngleCenter.SetLineWidth(LineWidth)
    PhiAngleCenter.Rebin(10)
    PhiAngleCenter.SetAxisRange(0, 1.1 * PhiAngleCenter.GetMaximum(), "Y")
    PhiAngleCenter.Draw()

    canvas.SaveAs("PhiAngleR20.png")

    PhiAngleCenter = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/PhiAngleR30")
    PhiAngleCenter.GetYaxis().SetTitleOffset(1.2)
    PhiAngleCenter.SetLineWidth(LineWidth)
    PhiAngleCenter.Rebin(10)
    PhiAngleCenter.SetAxisRange(0, 1.1 * PhiAngleCenter.GetMaximum(), "Y")
    PhiAngleCenter.Draw()

    canvas.SaveAs("PhiAngleR30.png")

    ComptonAngles = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/ComptonAngles")
    ComptonAngles.GetYaxis().SetTitleOffset(1.2)
    ComptonAngles.GetXaxis().SetTitle("#theta [deg]")
    ComptonAngles.SetLineWidth(LineWidth)
    ComptonAngles.Draw()
    line1 = TLine(33, 0, 33, 3000)
    line1.SetLineWidth(LineWidth)
    line2 = TLine(149, 0, 149, 3000)
    line2.SetLineWidth(LineWidth)
    line3 = TLine(35, 0, 35, 3000)
    line3.SetLineWidth(LineWidth)
    line3.SetLineStyle(2)
    line1.Draw("SAME")
    line2.Draw("SAME")
    line3.Draw("SAME")
    canvas.SaveAs("ComptonAngles.png")

    BTBvsAnnihilation = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/BTBhitsVsAnnihilation")
    BTBvsAnnihilation.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    BTBvsAnnihilation.GetXaxis().SetRangeUser(-0.5, 6.5)
    BTBvsAnnihilation.GetYaxis().SetRangeUser(-0.5, 30.5)
    BTBvsAnnihilation.Draw("COLZ")
    gPad.Update()
    move_stat_box(BTBvsAnnihilation)

    canvas.SetLogz(1)
    canvas.SaveAs("BTBvsAnnihilation.png")
    canvas.SetLogz(0)

    BTBxyPos = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_XY")
    BTBxyPos.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    BTBxyPos.Draw("COLZ")
    gPad.Update()
    move_stat_box(BTBxyPos)

    BTBxyPos.SetContour(150)
    canvas = even_axes(canvas)
    canvas.SaveAs("BTBxyPos.png")
    canvas.SetLogz(1)
    canvas.SaveAs("BTBxyPosLog.png")
    canvas.SetLogz(0)

    ThetaVsTheta = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/ThetaVsTheta")
    ThetaVsTheta.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    ThetaVsTheta.Draw("COLZ")
    gPad.Update()
    move_stat_box(ThetaVsTheta)

    canvas.SaveAs("ThetaVaTheta.png")
    canvas.SetLogz(1)
    canvas.SaveAs("ThetaVaThetaLog.png")
    canvas.SetLogz(0)
    line1 = TLine(0, 149, 200, 149)
    line1.SetLineWidth(LineWidth)
    line2 = TLine(0, 33, 200, 33)
    line2.SetLineWidth(LineWidth)
    line3 = TLine(33, 0, 33, 200)
    line3.SetLineWidth(LineWidth)
    line4 = TLine(149, 0, 149, 200)
    line4.SetLineWidth(LineWidth)
    line5 = TLine(0, 35, 200, 35)
    line5.SetLineWidth(LineWidth)
    line5.SetLineStyle(2)
    line6 = TLine(35, 0, 35, 200)
    line6.SetLineStyle(2)
    line1.Draw("SAME")
    line2.Draw("SAME")
    line3.Draw("SAME")
    line4.Draw("SAME")
    line5.Draw("SAME")
    line6.Draw("SAME")
    canvas.SaveAs("ThetaVaThetaLines.png")
    canvas.SetLogz(1)
    canvas.SaveAs("ThetaVaThetaLinesLog.png")
    canvas.SetLogz(0)

    DeltaVsDelta11 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta11")
    DeltaVsDelta11.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta11.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta11)

    canvas.SaveAs("DeltaVsDelta11.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog11.png")
    canvas.SetLogz(0)

    DeltaVsDelta12 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta12")
    DeltaVsDelta12.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta12.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta12)

    canvas.SaveAs("DeltaVsDelta12.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog12.png")
    canvas.SetLogz(0)

    DeltaVsDelta13 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta13")
    DeltaVsDelta13.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta13.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta13)

    canvas.SaveAs("DeltaVsDelta13.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog13.png")
    canvas.SetLogz(0)

    DeltaVsDelta21 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta21")
    DeltaVsDelta21.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta21.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta21)

    canvas.SaveAs("DeltaVsDelta21.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog21.png")
    canvas.SetLogz(0)

    DeltaVsDelta22 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta22")
    DeltaVsDelta22.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta22.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta22)

    canvas.SaveAs("DeltaVsDelta22.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog22.png")
    canvas.SetLogz(0)

    DeltaVsDelta23 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta23")
    DeltaVsDelta23.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta23.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta23)

    canvas.SaveAs("DeltaVsDelta23.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog23.png")
    canvas.SetLogz(0)

    DeltaVsDelta31 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta31")
    DeltaVsDelta31.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta31.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta31)

    canvas.SaveAs("DeltaVsDelta31.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog31.png")
    canvas.SetLogz(0)

    DeltaVsDelta32 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta32")
    DeltaVsDelta32.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta32.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta32)

    canvas.SaveAs("DeltaVsDelta32.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog32.png")
    canvas.SetLogz(0)

    DeltaVsDelta33 = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta33")
    DeltaVsDelta33.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta33.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta33)

    canvas.SaveAs("DeltaVsDelta33.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog33.png")
    canvas.SetLogz(0)

    DeltaVsDelta = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDelta")
    DeltaVsDelta.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDelta.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDelta)
    canvas.SaveAs("DeltaVsDelta.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLog.png")
    canvas.SetLogz(0)
    elipse1 = TEllipse(0.392458, -2.57843, 1.45, 0.7, 0, 360, 55.0)
    elipse2 = TEllipse(-2.40664, 0.492093, 1.45, 0.7, 0, 360, 35.0)
    elipse1.SetFillStyle(0)
    elipse1.SetLineWidth(LineWidth)
    elipse2.SetFillStyle(0)
    elipse2.SetLineWidth(LineWidth)
    elipse1.Draw("SAME")
    elipse2.Draw("SAME")
    canvas.SaveAs("DeltaVsDeltaElipse.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLogElipse.png")

    DeltaVsDeltaAfterCut = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/DeltaVsDeltaAfterCut")
    DeltaVsDeltaAfterCut.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    DeltaVsDeltaAfterCut.Draw("COLZ")
    gPad.Update()
    move_stat_box(DeltaVsDeltaAfterCut)

    canvas.SaveAs("DeltaVsDeltaAfterCut.png")
    canvas.SetLogz(1)
    canvas.SaveAs("DeltaVsDeltaLogAfterCut.png")
    canvas.SetLogz(0)

    BTBGamma_XY_cut = input_file.Get(
        "EventCategorizerEntanglement subtask 0 stats/2Gamma_XY_cut")
    BTBGamma_XY_cut.GetYaxis().SetTitleOffset(1.2)
    canvas.SetRightMargin(0.15)
    BTBGamma_XY_cut.Draw("COLZ")
    gPad.Update()
    move_stat_box(BTBGamma_XY_cut)

    BTBGamma_XY_cut.SetContour(150)
    canvas.SaveAs("BTBGamma_XY_cut.png")
    canvas.SetLogz(1)
    canvas.SaveAs("BTBGamma_XY_cutLog.png")
    canvas.SetLogz(0)


def even_axes(canvas):
    canvas.Update()
    xmin = canvas.GetUxmin()
    xmax = canvas.GetUxmax()
    ymin = canvas.GetUymin()
    ymax = canvas.GetUymax()

    xlength = xmax - xmin
    ylength = ymax - ymin
    ratio = xlength / ylength

    npx = canvas.GetWw()
    npy = canvas.GetWh()

    x1 = canvas.GetX1()
    y1 = canvas.GetY1()
    x2 = canvas.GetX2()
    y2 = canvas.GetY2()

    xlength2 = x2 - x1
    ylength2 = y2 - y1
    ratio2 = xlength2 / ylength2

    bnpx = canvas.GetWindowWidth()
    bnpy = canvas.GetWindowHeight()

    canvas.SetCanvasSize(int(round(npy * ratio2)), int(npy))
    canvas.SetWindowSize(int((bnpx - npx) + round(npy * ratio2)), int(bnpy))
    return canvas


def move_stat_box(histogram):
    statistics = histogram.FindObject("stats")
    oldX1 = statistics.GetX1()
    oldY1 = statistics.GetY1()
    oldX2 = statistics.GetX2()
    oldY2 = statistics.GetY2()

    lenX = (oldX2 - oldX1)
    lenY = (oldY2 - oldY1)
    X = histogram.GetXaxis().GetXmax()
    Y = histogram.GetYaxis().GetXmax()

    statistics.SetX2(X)
    statistics.SetY2(Y)
    statistics.SetX1(X - lenX)
    statistics.SetY1(Y - lenY)


def elipse(x, y, X0, Y0, a, b, theta):
    return ((x - X0) * cos(theta) + (y - Y0) * sin(theta))**2 / a**2 + \
        ((x - X0) * sin(theta) + (y - Y0) * cos(theta))**2 / b**2


if __name__ == "__main__":
    main()
