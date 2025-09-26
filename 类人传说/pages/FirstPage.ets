import { Player } from '../other/models'


@Entry
@Component
export default struct FirstPage{
  @StorageProp('time') time: number = 0;
  @StorageLink('player') player: Player = new Player();
  build(){
    Stack({}){
      Column({space:20}){
        Row(){
          Column(){
            Image($r("app.media.person2"))
              .margin({top:5})
              .width(40)
              .height(40)
              .borderRadius(20)
              .backgroundColor(Color.Gray)
            Text(this.player.name)
          }
          .width('20%')
          Blank()
          Text(`道历${this.time}年`)
        }
        .width('100%')
        .backgroundColor('#795f1414')
        Image($r('app.media.person1'))
          .width(300)
          .height(300)
        Text(`修为 ${this.player.qi}`)
        Button('突破')
          .width(100)
      }
      .width('100%')
      .height('100%')
    }
  }
}