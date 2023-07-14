import torch
from torchvision.models import vgg16, VGG16_Weights
from torchvision.models import resnet50, ResNet50_Weights
from torchvision import transforms, datasets
import numpy as np
import matplotlib.pyplot as plt
from torch.utils.data import DataLoader
import os
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt
import os

#Firs I read datasets and adjusted cuda. I did all my homework in Colab, so thanks to colab I used GPU.
dataset_dir = "/content/drive/MyDrive"
train_dir = dataset_dir + "/train"
valid_dir = dataset_dir + "/valid"
test_dir = dataset_dir + "/test"
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')


data_transform = transforms.Compose([
        transforms.Resize(256),
        transforms.CenterCrop(224),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
    ])

# Here is a simple function to transform train and valid datasets.
def load_data(data_dir, transform):
    dataset = datasets.ImageFolder(data_dir, transform=transform)
    return dataset


train_dataset = load_data(train_dir, data_transform)
valid_dataset = load_data(valid_dir, data_transform)
train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
valid_loader = DataLoader(valid_dataset, batch_size=32, shuffle=False)

# I choosed and initialized models for training. Then I deleted their last layers.
resnet = resnet50(pretrained=True)
vg16 = vgg16(pretrained=True)
vg16.classifier = None
resnet.fc = None
# Freezed layers
for param in vg16.parameters():
    param.requires_grad = False

for param in resnet.parameters():
    param.requires_grad = False

#Added traineble last layers according to Binary Classification.
resnet.fc = nn.Sequential(
    nn.Linear(2048, 1),
    nn.Sigmoid()
)
resnet = resnet.to(device)

vg16.classifier = torch.nn.Sequential(
    torch.nn.Linear(25088, 4096),
    torch.nn.ReLU(True),
    torch.nn.Dropout(),
    torch.nn.Linear(4096, 4096),
    torch.nn.ReLU(True),
    torch.nn.Dropout(),
    torch.nn.Linear(4096, 1),
    nn.Sigmoid()
)
vg16 = vg16.to(device)

train_accs_vgg16 = []
valid_accs_vgg16 = []
train_accs_resnet = []
valid_accs_resnet = []
# Here is my function for training
def train_model(dataloader, model, criterion, optimizer, device):
    model.train()
    running_loss = 0.0
    running_corrects = 0
    total = 0

    for inputs, labels in dataloader:
        inputs = inputs.to(device)
        labels = torch.where(labels == 0, 1, 0)
        labels = labels.unsqueeze(1).float().to(device)
        optimizer.zero_grad()

        outputs = model(inputs)
        # I take threshold as 0.4 because most of the images were 0, and it causes imbalance. With choosing threshold low,
        # I get some more balanced training. I did the same thing in the validation function too.
        preds = (outputs > 0.4).float()
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        running_loss += loss.item() * inputs.size(0)
        running_corrects += torch.sum(preds == labels.data)
        total += labels.size(0)
    # Calculated train losses and accuracies.
    epoch_loss = running_loss / total
    epoch_acc = running_corrects.double() / total

    return epoch_loss, epoch_acc
# Here is my validation function.
def validate_model(dataloader, model, criterion, device):
    model.eval()
    running_loss = 0.0
    running_corrects = 0
    total = 0

    with torch.no_grad():
        for inputs, labels in dataloader:
            inputs = inputs.to(device)
            # Below, I converted classes to 0 and 1. I did the same thing in the validation too.
            labels = torch.where(labels == 0, 1, 0)
            labels = labels.unsqueeze(1).float().to(device)

            outputs = model(inputs)
            preds = (outputs > 0.4).float()
            loss = criterion(outputs, labels)

            running_loss += loss.item() * inputs.size(0)
            running_corrects += torch.sum(preds == labels.data)
            total += labels.size(0)

    epoch_loss = running_loss / total
    epoch_acc = running_corrects.double() / total

    return epoch_loss, epoch_acc
# Since we are doing Binary Classification, I used BCELoss. For optimizer, according to my researches using Adam is the best.
num_epochs = 10
criterion = torch.nn.BCELoss()
optimizer_resnet = torch.optim.Adam(resnet.fc.parameters(), lr=0.0001)
optimizer_vgg16 = torch.optim.Adam(vg16.classifier.parameters(), lr=0.0001)
# Here is the training and validation parts with 10 epochs.
for epoch in range(num_epochs):
    print(f'Epoch {epoch+1}/{num_epochs}')
    print('-' * 10)
    
    train_lossvgg, train_accvgg = train_model(train_loader, vg16, criterion, optimizer_vgg16, device)
    valid_lossvgg, valid_accvgg = validate_model(valid_loader, vg16, criterion, device)

    train_accs_vgg16.append(train_accvgg)
    valid_accs_vgg16.append(valid_accvgg)

    print(f'Training VGG16: Loss: {train_lossvgg:.4f} Acc: {train_accvgg:.4f}')
    print(f'Validation VGG16: Loss: {valid_lossvgg:.4f} Acc: {valid_accvgg:.4f}')
    # I saved weights to use them later in the testing.
    torch.save({
        'epoch': epoch,
        'model_state_dict': vg16.state_dict(),
        'optimizer_state_dict': optimizer_vgg16.state_dict(),
        'loss': train_lossvgg,
    }, f"/content/drive/MyDrive/vgg16_epoch_{epoch+1}_new.pt")

    train_loss, train_acc = train_model(train_loader, resnet, criterion, optimizer_resnet, device)
    valid_loss, valid_acc = validate_model(valid_loader, resnet, criterion, device)
    train_accs_resnet.append(train_acc)
    valid_accs_resnet.append(valid_acc)

    print(f'Training ResNet50: Loss: {train_loss:.4f} Acc: {train_acc:.4f}')
    print(f'Validation ResNet50: Loss: {valid_loss:.4f} Acc: {valid_acc:.4f}')

    torch.save({
        'epoch': epoch,
        'model_state_dict': resnet.state_dict(),
        'optimizer_state_dict': optimizer_resnet.state_dict(),
        'loss': train_loss,
    }, f"/content/drive/MyDrive/resnet_epoch_{epoch+1}_new.pt")