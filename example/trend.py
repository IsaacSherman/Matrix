#age: continuous.
#workclass: Private, Self-emp-not-inc, Self-emp-inc, Federal-gov, Local-gov, State-gov, Without-pay, Never-worked.
#fnlwgt: continuous.
#education: Bachelors, Some-college, 11th, HS-grad, Prof-school, Assoc-acdm, Assoc-voc, 9th, 7th-8th, 12th, Masters, 1st-4th, 10th, Doctorate, 5th-6th, Preschool.
#education-num: continuous.
#marital-status: Married-civ-spouse, Divorced, Never-married, Separated, Widowed, Married-spouse-absent, Married-AF-spouse.
#occupation: Tech-support, Craft-repair, Other-service, Sales, Exec-managerial, Prof-specialty, Handlers-cleaners, Machine-op-inspct, Adm-clerical, Farming-fishing, Transport-moving, Priv-house-serv, Protective-serv, Armed-Forces.
#relationship: Wife, Own-child, Husband, Not-in-family, Other-relative, Unmarried.
#race: White, Asian-Pac-Islander, Amer-Indian-Eskimo, Other, Black.
#sex: Female, Male.
#capital-gain: continuous.
#capital-loss: continuous.
#hours-per-week: continuous.
#native-country: United-States, Cambodia, England, Puerto-Rico, Canada, Germany, Outlying-US(Guam-USVI-etc), India, Japan, Greece, South, China, Cuba, Iran, Honduras, Philippines, Italy, Poland, Jamaica, Vietnam, Mexico, Portugal, Ireland, France, Dominican-Republic, Laos, Ecuador, Taiwan, Haiti, Columbia, Hungary, Guatemala, Nicaragua, Scotland, Thailand, Yugoslavia, El-Salvador, Trinadad&Tobago, Peru, Hong, Holand-Netherlands.
#What I'll do is  grab an entire line into an associative array, and use these labels as the key for the kvp
#Then I can do a foreach on all of the labels here, so the code might look something like:
#while(stdin){
# Array A = line;
#w1=w2=0;
#if A[0] == continuous continue;
#else for each label l in A[0]:
#   if(A['class'] == 1) w1 +=1;
#   else w2+=1;
#Code for missing data (essentially just continue)

from __future__ import division #for floating point behavior
import re
def fileLen(fname):
    """

    :rtype : int
    """
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1



def countLabelsMatching(Label, LabelIndex, ClassIndex, fileName):
    ### Assume classes is 1 indexed, but label and class are 0 indexed
    """

    :rtype : int, int
    """
    ret1=ret2=0#ret1 is class1 count matching label, ret2 is class2 count matching label
    file = open(fileName, 'r')
    for line in file:
        line = line.strip()
        records = line.split(", ")
        if records[LabelIndex] == Label:
            #print("records[labelIndex] = ", records[LabelIndex], "Class = ", records[ClassIndex])
            if records[ClassIndex] == '1':
                ret1 += 1
            else:
                ret2 += 1
    return ret1, ret2

def dumpValues(fileName, list, index):
    """
    :param fileName: string with the name of the file
    :param list: list of strings to dump into the list
    :param index: index of the record we're dumping
    :return: none, changes are made in place
    """
    file = open(fileName)

    for i in range(0, fileLen(fileName)):
        line = file.readline()
        line = line.strip()
        record = line.split(', ')
        list[i] += record[index]+' '

def replaceLabelsWithValues(list, label, value):
    """
    :param list: list of strings to search
    :param label: string to look for
    :param value: string to replace label with
    :return: none
        """
    for i in range(0, len(list)):
        list[i] = re.sub(label, value, list[i])



age = ["continuous"]
workclass = ["Private", "Self-emp-not-inc", "Self-emp-inc", "Federal-gov", "Local-gov",
             "State-gov", "Without-pay", "Never-worked"]
fnlwgt = ["continuous"]
education = ["Bachelors", "Some-college", "11th", "HS-grad", "Prof-school", "Assoc-acdm",
             "Assoc-voc", "9th", "7th-8th", "12th", "Masters", "1st-4th", "10th",
             "Doctorate", "5th-6th", "Preschool"]
educationNum = ["continuous"]
marital = ["Married-civ-spouse", "Divorced", "Never-married", "Separated", "Widowed",
           "Married-spouse-absent", "Married-AF-spouse"]
occupation = ["Tech-support", "Craft-repair", "Other-service", "Sales", "Exec-managerial",
              "Prof-specialty", "Handlers-cleaners", "Machine-op-inspct", "Adm-clerical",
              "Farming-fishing", "Transport-moving", "Priv-house-serv", "Protective-serv", "Armed-Forces."]
relationship = ["Wife", "Own-child", "Husband", "Not-in-family", "Other-relative", "Unmarried"]
race = ["White", "Asian-Pac-Islander", "Amer-Indian-Eskimo", "Other", "Black"]

sex = ["Female", "Male"]
capitalGain = ["continuous"]
capitalLoss = ["continuous"]
HoursPerWeek = ["continuous"]
NativeCountry = ["United-States", "Cambodia", "England", "Puerto-Rico", "Canada", "Germany",
                 "Outlying-US(Guam-USVI-etc)", "India", "Japan", "Greece", "South", "China",
                 "Cuba", "Iran", "Honduras", "Philippines", "Italy", "Poland", "Jamaica",
                 "Vietnam", "Mexico", "Portugal", "Ireland", "France", "Dominican-Republic",
                 "Laos", "Ecuador", "Taiwan", "Haiti", "Columbia", "Hungary", "Guatemala",
                 "Nicaragua", "Scotland", "Thailand", "Yugoslavia", "El-Salvador", "Trinadad&Tobago",
                 "Peru", "Hong", "Holand-Netherlands"]
Categories = [age, workclass, fnlwgt,education, educationNum, marital, occupation, relationship, race, sex,
              capitalGain, capitalLoss, HoursPerWeek, NativeCountry]
#Now all the categories are set up.  Now we want to get the file.
files = ['adult.1', 'adult.2', 'adult.3']
filesout = ['adult1.tr', 'adult2.tr', 'adult3.tr']

lenFile=[fileLen(files[0]), fileLen(files[1]), fileLen(files[2])]

for i in range(0,3):
    outlines=[[],[],[]]#These hold the lines that will be written, since we have to write in order
    fin = open(files[i], 'r')
    outlines[i] = fin.readlines()
    for j in range(0, len(Categories)):
        for k in range(0, len(Categories[j])):
            if(Categories[j][k] == 'continuous'):
                continue
            else:
                countw1, countw2=  countLabelsMatching(Label=Categories[j][k], LabelIndex=j,
                                               ClassIndex = 14, fileName=files[i])
                print("Labels matching ", Categories[j][k], countw1, countw2)
                greater = max(countw1,countw2)
                val = greater/lenFile[i]
                print(val, greater, lenFile[i])
                val = str(val)
                replaceLabelsWithValues(list=outlines[i], label=Categories[j][k], value=val)
    replaceLabelsWithValues(list=outlines[i], label="\?", value= "-1")
    fout = open(filesout[i], 'w')
    print("outfile = ",filesout[i])
    fout.writelines(outlines[i])



