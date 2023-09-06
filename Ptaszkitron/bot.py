import discord
from discord.ext import commands

TOKEN = 'token here'

intents = discord.Intents.default()
intents.members = True
intents.message_content = True

client = discord.Client(activity=discord.Activity(name='Lives in computer'), intents=intents)
client = commands.Bot(command_prefix='.', intents=intents)

@client.event 
async def on_ready():
    print(f'Bot is ready. {client.user}')

@client.event
async def on_member_join(member):
    print(f'{member} has joined a server.')

@client.event
async def on_member_remove(member):
    print(f'{member} has left a server.')

@client.listen('on_message')
async def on_message(message):
    print(f'Message: {message.author} ULink=({message.author.id}) :: "{message.content}"\nAddress: {message.channel} ChLink=({message.channel.id}), MLink=({message.id})')
    if message.author == client.user: return

    if message.content.startswith('hi bot'):
        await message.channel.send('hi human')
    if message.content.startswith('dm me bot'):
        await message.author.send('hello there :D')

@client.command(name='ping')
async def ping(ctx):
    await ctx.send(f'Ping: {round(client.latency * 1000)}ms')

@client.command(name='send')
async def send(ctx, animal):
    if animal == 'cat':
        await ctx.message.add_reaction('🐈')
        await ctx.send(f'here\'s cat', file=discord.File('send_cat.jpg'))
    if animal == 'dog':
        await ctx.message.add_reaction('🐕')
        await ctx.send(f'here\'s dog', file=discord.File('send_dog.jpg'))

@client.command(name='find')
async def find(ctx, word):
    print(ctx.message.channel.id)
    from_channel = client.get_channel(ctx.message.channel.id)
    messages = []
    async for msg in from_channel.history(limit=200):
        messages.append(msg)
    if messages:
        print(messages[-1].jump_url)
        await ctx.send(f'Url for the first channel message: {str(messages[0].jump_url)}')
client.run(TOKEN)