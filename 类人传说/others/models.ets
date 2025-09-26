import {promptAction} from '@kit.ArkUI'

let stateList: string[] = [
  '练气', '筑基', '金丹', '元婴',
  '化神', '合体', '大乘', '渡劫',
]



interface Person{
  name: string;
  qi: number;
  qiSpeed: number;
  stateNum: number;
  state: string;
}

export class Player implements Person{
  name: string = '哈哈怪';
  qi: number = 0;
  qiSpeed: number = 1;
  stateNum: number = 0;
  state: string = stateList[this.stateNum];



  breakState(){
    if (this.qi / Math.pow(10, this.stateNum) >= 1){
      this.stateNum++
      this.qiSpeed++
      this.state = stateList[this.stateNum]
    }
    else promptAction.showToast({message:"修为不足\n无法突破"})
  }
}


interface ItemInterface{
  id: number;
  name: string;
  quantity: string;
  effectType: string;
  effectNum: number;
  info: string;
  price: number;
}

export class Item{
  id: number = 0;
  name: string = '不知名物品';
  quantity: string = '';
  effectType: string = '';
  effectNum: number = 0;
  info: string = '这个物品很神秘，没有什么关于它的介绍';
  price: number = 1;

  constructor(id: number = 0, name: string = '不知名物品', quantity: string = '', effectType: string = '', effectNum: number = 0, info: string = '这个物品很神秘，没有什么关于它的介绍', price: number = 1) {
    this.id = id;
    this.name = name;
    this.quantity = quantity;
    this.effectType = effectType;
    this.effectNum = effectNum;
    this.info = info;
    this.price = price;
  }
}