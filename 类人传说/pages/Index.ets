import FirstPage from './FirstPage'

@Entry
@Component
struct Index{
  @State barNames: string[] = ['修炼', '背包', '功法', '门派', '洞府', '秘境', '机缘']
  @Builder
  contentBuilder(name: string){
    if (name == '修炼') FirstPage()
    else Text(name)
  }
  build(){
    Tabs({barPosition:BarPosition.End}){
      ForEach(this.barNames, (barName: string)=>{
        TabContent(){
          this.contentBuilder(barName)
        }
        .tabBar(barName)
        .maxSize()
      })
    }
    .maxSize()
  }
}

@Styles
function maxSize(){
  .width('100%')
  .height('100%')
}