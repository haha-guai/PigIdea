import { promptAction, router} from '@kit.ArkUI'
//路由跳转其他页面

@Entry
@Component
struct Start {
  build(){
    Tabs({barPosition:BarPosition.End}){

      TabContent(){
        page1()
      }
      .tabBar("登录")
      .width('100%')
      .height('100%')
      .padding({left:20, right:20})


      TabContent(){
        page2()
      }
      .tabBar("注册")
      .padding({left:20, right:20})
    }
    .width('100%')
    .height('100%')
  }
}


@Component
struct page1{
  build(){
    Column({space:20}){
      Image($r("app.media.person1"))
        .width(100)
        .height(100)
        .borderRadius(50)
        .backgroundColor(Color.Gray)
        .margin({top:50})
      Row({space:20}){
        Text("账号")
          .width('10%')
        TextInput()
          .width('80%')
      }
      .width('100%')
      Row({space:20}){
        Text("密码")
          .width('10%')
        TextInput()
          .width('80%')
          .type(InputType.Password)
      }
      .width('100%')
      Button('登录')
        .width(150)
        .margin({top:50})
        .onClick(()=>{
          if (check1()) {
            console.log('111');
            router.pushUrl({ url: 'pages/Index', params: null });
            console.log('666');
          }
          else promptAction.showToast({message:'登录失败'});// PigWork
        })
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct page2{
  build(){
    Column({space:20}){
      Image($r("app.media.person1"))
        .width(100)
        .height(100)
        .borderRadius(50)
        .backgroundColor(Color.Gray)
        .margin({top:50})
      Row({space:20}){
        Text("账号")
          .width('10%')
        TextInput()
          .width('80%')
      }
      .width('100%')
      Row({space:20}){
        Text("密码")
          .width('10%')
        TextInput()
          .width('80%')
          .type(InputType.Password)
      }
      .width('100%')
      Row({space:20}){
        Text("确认密码")
          .width('10%')
        TextInput()
          .width('80%')
          .type(InputType.Password)

      }
      .width('100%')
      Button('注册')
        .width(150)
        .margin({top:50})
        .onClick(()=>{
          if (check2()) router.pushUrl({url:'pages/Index', params:null});
          else promptAction.showToast({message:'注册失败'});// PigWork
        })
    }
    .width('100%')
    .height('100%')
  }
}

// PigWork
function check1(): boolean{
  return true;
}

// PigWork
function check2(): boolean{
  return true;
}