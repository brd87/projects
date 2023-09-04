import discord
from discord.ext import commands

TOKEN = 'token here'



intents = discord.Intents.default()
intents.message_content = True

client = commands.Bot(command_prefix='.', intents=intents)

@client.event 
async def on_ready():
    print("Bot is ready.")

@client.event
async def on_member_join(member):
    print(f"{member} has joined a server.")

@client.event
async def on_member_remove(member):
    print(f"{member} has left a server.")

@client.event
async def on_message(message):
    print(f"Message: {message.author} ULink=({message.author.id}) :: \"{message.content}\"\nAddress: {message.channel} ChLink=({message.channel.id}), MLink=({message.id})")

@client.command()
async def ping(ctx):
    await ctx.send(f'Ping: {round(client.latency * 1000)}ms')

client.run(TOKEN)